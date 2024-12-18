/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:01:13 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 14:01:49 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	*get_buffer(void *img)
{
	int	bpp;
	int	sizeline;
	int	endian;

	return ((int *)mlx_get_data_addr(img, &bpp, &sizeline, &endian));
}

void	draw_square(void *img, int x, int y, int color)
{
	int	i;
	int	j;
	int	*buffer;

	buffer = get_buffer(img);
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			buffer[(y + i) * WIN_WIDTH + (x + j)] = color;
			j++;
		}
		i++;
	}
}

void	draw_camera_tip(int *buffer, int x, int y, double angle)
{
	int	i;
	int	arrow_length = 10;
	int	arrow_width = 3;

	i = -arrow_width;
	while (i <= arrow_width)
	{
		int	dx = (int)((arrow_length - 1) * cos(angle));
		int	dy = (int)((arrow_length - 1) * sin(angle));
		int	wx = (int)(i * cos(angle + M_PI_2));
		int	wy = (int)(i * sin(angle + M_PI_2));
		buffer[(y + dy + wy) * WIN_WIDTH + (x + dx + wx)] = MINIMAP_PLAYER_COLOR;
		i++;
	}
	i = -arrow_width + 1;
	while (i <= arrow_width - 1)
	{
		int	dx = (int)((arrow_length - 2) * cos(angle));
		int	dy = (int)((arrow_length - 2) * sin(angle));
		int	wx = (int)(i * cos(angle + M_PI_2));
		int	wy = (int)(i * sin(angle + M_PI_2));
		buffer[(y + dy + wy) * WIN_WIDTH + (x + dx + wx)] = MINIMAP_PLAYER_COLOR;
		i++;
	}
}

void	draw_camera(void *img, int x, int y, double angle)
{
	int	i;
	int	*buffer;
	int	arrow_length;
	int	arrow_width;

	arrow_length = 10;
	arrow_width = 3;
	buffer = get_buffer(img);
	i = 0;
	while (i < arrow_length - 3)
	{
		int	dx = (int)(i * cos(angle));
		int	dy = (int)(i * sin(angle));
		int	w = -arrow_width;
		while (w <= arrow_width)
		{
			int	wx = (int)(w * cos(angle + M_PI_2));
			int	wy = (int)(w * sin(angle + M_PI_2));
			buffer[(y + dy + wy) * WIN_WIDTH + (x + dx + wx)] = MINIMAP_PLAYER_COLOR;
			w++;
		}
		i++;
	}
	draw_camera_tip(buffer, x, y, angle);
}