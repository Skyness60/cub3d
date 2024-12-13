/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:59 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/13 16:33:47 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ceiling_and_top(t_raycast *raycast, int size_img)
{
	int	i;

	i = WIN_HEIGHT / 2 - size_img / 2 + 1;
	while (--i > 0)
		raycast->new_buff[(int)(i * WIN_WIDTH + raycast->count_r)] = 0;
	i = WIN_HEIGHT / 2 + size_img / 2 - 1;
	while (++i < WIN_HEIGHT)
		raycast->new_buff[(int)(i * WIN_WIDTH + raycast->count_r)] = 0;
}

static void	fill_column_bis(t_raycast *raycast, t_texture texture, \
								int size_img, int ratio)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = WIN_HEIGHT / 2 - size_img - 1; 
	while (++i < texture.height)
	{
		while (++j < ratio)
			raycast->new_buff[(int)(++k * WIN_WIDTH + raycast->count_r)] = \
			texture.buffer[(int)(i * texture.width + texture.width * \
			raycast->precise_hit)];
		j = -1;
	}
}

static void	fill_column(t_raycast *raycast, t_texture texture)
{
	double	len;
	int		col_size;
	int		i;
	int		ratio;
	
	i = -1;
	if (raycast->x == 1)
		len = raycast->len_x;
	else
		len = raycast->len_y;
	col_size = PROJ_PLANE_DT / (len / 2);
	if (col_size > WIN_HEIGHT)
		col_size = WIN_HEIGHT;
	ratio = col_size / texture.height;
	while (++i < col_size)
		fill_column_bis(raycast, texture, col_size, ratio);
	ceiling_and_top(raycast, col_size);
}

void	construct_img(t_data *data, t_raycast *raycast)
{
	int	bpp;
	int	sizeline;
	int	endian;
	
	raycast->new_img = mlx_new_image(data->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	raycast->new_buff = (int *)(mlx_get_data_addr(raycast->new_img, &bpp, \
	&sizeline, &endian));
	if (raycast->x == 1 && raycast->angle > PI / 2 && \
	raycast->angle < PI + PI / 2)
		fill_column(raycast, data->cub->texture[WEST]);
	else if (raycast->x == 1)
		fill_column(raycast, data->cub->texture[EAST]);
	else if (raycast->angle < PI)	
		fill_column(raycast, data->cub->texture[NORTH]);
	else
		fill_column(raycast, data->cub->texture[NORTH]);
}
