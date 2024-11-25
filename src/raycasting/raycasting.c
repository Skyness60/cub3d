/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/25 09:01:14 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_cells_bis(double delta, bool x, char **map, 
								t_raycasting *raycasting)
{
	double	projection_height;
	double	distance;
	int		sprite_top;
	int		sprite_bottom;
	int		i;

	i = -1;
	if (x)
		distance = raycasting->count_delta_x * delta;
	else
		distance = raycasting->count_delta_y * delta;
	projection_height = PROJ_PLANE_DT * CELL_SIZE / distance;
	sprite_top = (WIN_HEIGHT / 2) - (projection_height / 2);
	sprite_bottom = (WIN_HEIGHT / 2) + (projection_height / 2);
	if (sprite_top < 0)
		sprite_top = 0;
	if (sprite_bottom > WIN_HEIGHT)
		sprite_bottom = WIN_HEIGHT;
	//afficher les spites;
}

static void	display_cells(t_raycasting *raycasting, double delta_x,
						double delta_y,	t_map *map)
{	
	while (1)
	{
		if (raycasting->step_x > raycasting->step_y)
		{
			raycasting->to_next_cell_x += raycasting->step_x;
			display_cells_bis(delta_x, 1, map->map_copy, raycasting);
			if (map->map_copy[raycasting->step_y][raycasting->step_x] == '1')
				break ;					
		}
		else
		{
			raycasting->to_next_cell_y += raycasting->step_y;
			display_cells_bis(delta_y, 0, map->map_copy, raycasting);
			if (map->map_copy[raycasting->step_y][raycasting->step_x] == '1')
				break ;			
		}
	}	
}

static void	send_rays(t_data *data, t_player *player, double ray_angle)
{
	double	delta_x;
	double	delta_y;

	delta_x = CELL_SIZE / fabs(cos(ray_angle));
	delta_y = CELL_SIZE / fabs(sin(ray_angle));
	if (cos(ray_angle) > 0)
		data->raycasting->step_x = 1;
	else
		data->raycasting->step_x = 1;
	if (sin(ray_angle) > 0)
		data->raycasting->step_y = 1;
	else
		data->raycasting->step_y = -1;
	data->raycasting->to_next_cell_x = player->x;
	data->raycasting->to_next_cell_y = player->y;
	data->raycasting->dt_to_1st_cell_x = player->x - (int)player->x;
	data->raycasting->dt_to_1st_cell_y = player->y - (int)player->y;
	display_cells(data->raycasting, delta_x, delta_y, data->cub->map->map_copy);
}

static void	raycast_bis(t_data *data)
{
	double	ray_angle;
	double	cam_angle;
	int		i;

	i = 0;
	cam_angle = data->player->angle;
	while (i < WIN_WIDTH)
	{
		ray_angle = cam_angle - (FOV / 2) + (i * FOV / WIN_WIDTH);
		send_rays(data, data->player, ray_angle);
		i++;
	}
}

void	raycast(t_data *data)
{
	data->raycasting->count_delta_x = 0;
	data->raycasting->count_delta_y = 0;
	data->raycasting->data = data;
	if (data->spawn == 1)
	{
		{
			if (data->player->orientation == 'N')
				data->player->angle = PI / 2;
			else if (data->player->orientation == 'E')
				data->player->angle = 2 * PI;
			else if (data->player->orientation == 'W')
				data->player->angle = PI;
			else if (data->player->orientation == 'S')
				data->player->angle = 3 * PI / 2;
			data->spawn = 0;
		}
	}
	raycast_bis(data);
}
