/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:59 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/30 11:43:17 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void	draw_ceiling_and_floor(t_raycast *raycast, int col_size)
{
	int	i;

	i = -1;
	while (++i < WIN_HEIGHT / 2 - col_size / 2)
		raycast->new_buff[i * WIN_WIDTH + raycast->count_r] \
		= raycast->data->cub->hex_ceiling;
	i = WIN_HEIGHT / 2 + col_size / 2 - 1;
	while (++i < WIN_HEIGHT)
		raycast->new_buff[i * WIN_WIDTH + raycast->count_r] \
		= raycast->data->cub->hex_floor;
}

void	draw_column(t_raycast *raycast, t_texture texture, int col_size, int i)
{
	int		screen_pos;
	int		tex_x;
	double	ratio;
	double	tex_y;
	int		screen_y;

	screen_pos = WIN_HEIGHT / 2 - col_size / 2;
	tex_x = (int)(texture.width * fmod(raycast->precise_hit, 1.0));
	ratio = (double)texture.height / col_size;
	tex_y = 0.0;
	i = -1;
	while (++i < col_size)
	{
		screen_y = screen_pos + i;
		if (screen_y >= 0 && screen_y < WIN_HEIGHT)
		{
			raycast->new_buff[screen_y * WIN_WIDTH + raycast->count_r] = \
				texture.buffer[(int)tex_y * texture.width + tex_x];
		}
		tex_y += ratio;
	}
}

void	fill_column(t_raycast *raycast, t_texture texture)
{
	double	len;
	int		col_size;

	len = 0;
	if (raycast->x == 1)
		len = raycast->len_x;
	else
		len = raycast->len_y;
	col_size = (int)((WIN_HEIGHT / PROJ_PLANE) / len);
	if (col_size > WIN_HEIGHT)
		col_size = WIN_HEIGHT;
	draw_column(raycast, texture, col_size, -1);
	if (col_size < WIN_HEIGHT)
		draw_ceiling_and_floor(raycast, col_size);
}

void	construct_img(t_data *data, t_raycast *raycast)
{
	if (raycast->x == 1 && raycast->angle >= PI / 2 && \
	raycast->angle <= PI + PI / 2)
		fill_column(raycast, data->cub->texture[WEST]);
	else if (raycast->x == 1)
		fill_column(raycast, data->cub->texture[EAST]);
	else if (raycast->angle <= PI)
		fill_column(raycast, data->cub->texture[SOUTH]);
	else
		fill_column(raycast, data->cub->texture[NORTH]);
}
