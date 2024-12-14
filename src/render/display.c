/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:59 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/14 17:56:00 by jlebard          ###   ########.fr       */
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
	k = WIN_HEIGHT / 2 - size_img / 2 - 1; 
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
	if (raycast->count_r == 100)
		printf("real len : %f\n", len);
	if (len < 0.25)
		len = 0.25;
	col_size = WIN_HEIGHT / len;
	if (col_size > WIN_HEIGHT)
		col_size = WIN_HEIGHT;
	if (raycast->count_r == 100)
	{
		printf("len = %f\n", len);
		printf("col_size : %d\n", col_size);
	}
	ratio = col_size / texture.height;
	while (++i < col_size)
		fill_column_bis(raycast, texture, col_size, ratio);
	if (col_size < WIN_HEIGHT)
		ceiling_and_top(raycast, col_size);
}

void	construct_img(t_data *data, t_raycast *raycast)
{
	if (raycast->x == 1 && raycast->angle > PI / 2 && \
	raycast->angle < PI + PI / 2)
		fill_column(raycast, data->cub->texture[WEST]);
	else if (raycast->x == 1)
		fill_column(raycast, data->cub->texture[EAST]);
	else if (raycast->angle < PI)	
		fill_column(raycast, data->cub->texture[NORTH]);
	else
		fill_column(raycast, data->cub->texture[SOUTH]);
}
