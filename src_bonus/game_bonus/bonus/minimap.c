/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:34:17 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 14:05:45 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(void *img, int x, int y, double angle)
{
	draw_camera(img, x, y, angle);
}

static void	draw_background(void *img, int map_width, int map_height)
{
	int	x;
	int	y;
	int	*buffer;

	buffer = get_buffer(img);
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			buffer[y * WIN_WIDTH + x] = MINIMAP_BACKGROUND_COLOR;
			x++;
		}
		y++;
	}
}

static void	draw_walls(void *img, t_data *data)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = 0;
	while (y < data->cub->map->height)
	{
		x = 0;
		while (x < data->cub->map->width)
		{
			if (data->cub->map->map[y][x] == '1')
			{
				map_x = x * 10;
				map_y = y * 10;
				draw_square(img, map_x, map_y, 0x000000);
			}
			x++;
		}
		y++;
	}
}

static void	draw_borders(void *img, int map_width, int map_height)
{
	int	x;
	int	y;
	int	*buffer;

	buffer = get_buffer(img);
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (y == 0 || y == map_height - 1 || x == 0 || x == map_width - 1)
				buffer[y * WIN_WIDTH + x] = 0x000000;
			x++;
		}
		y++;
	}
}

void	*minimap(t_data *data, void *img)
{
	int	map_x;
	int	map_y;
	int	map_width;
	int	map_height;

	map_width = data->cub->map->width * 10;
	map_height = data->cub->map->height * 10;
	draw_background(img, map_width, map_height);
	draw_walls(img, data);
	map_x = data->player->x * 10;
	map_y = data->player->y * 10;
	draw_player(img, map_x, map_y, data->player->angle);
	draw_borders(img, map_width, map_height);
	return (img);
}
