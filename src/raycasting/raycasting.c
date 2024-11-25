/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/25 13:55:41 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_cells_bis(double distance, bool x, t_raycasting *raycasting)
{
	double	projection_height;
	int		i;

	i = -1;
	projection_height = PROJ_PLANE_DT / distance;
	if (raycasting->visited[(int)raycasting->y][(int)raycasting->x] == 1)
		return ;
	raycasting->visited[(int)raycasting->y][(int)raycasting->x] = 1;
	display_texture(raycasting, x, projection_height);
}

static void	display_cells(t_raycasting *raycasting, double delta_x,
						double delta_y,	t_map *map)
{	
	raycasting->to_next_cell_x = ((int)raycasting->x - raycasting->x) / delta_x;
	raycasting->to_next_cell_y = ((int)raycasting->y - raycasting->y) / delta_y;
	while (1)
	{
		if (raycasting->to_next_cell_x < raycasting->to_next_cell_y)
		{
			raycasting->x += raycasting->step_x;
			raycasting->to_next_cell_x = raycasting->to_next_cell_x + delta_x;
			if (map->map_copy[(int)raycasting->y][(int)raycasting->x] == '1')
				return (display_cells_bis(delta_x, 1, raycasting), \
				NULL);
		}
		else
		{
			raycasting->y += raycasting->step_y;
			raycasting->to_next_cell_y = raycasting->to_next_cell_y + delta_y;
			if (map->map_copy[(int)raycasting->y][(int)raycasting->x] == '1')
				return (display_cells_bis(delta_y, 0, raycasting), \
				NULL);
		}
	}	
}

static void	send_rays(t_data *data, t_player *player, double ray_angle)
{
	double	delta_x;
	double	delta_y;

	delta_x = 1 / fabs(cos(ray_angle));
	delta_y = 1 / fabs(sin(ray_angle));
	if (cos(ray_angle) > 0)
		data->raycasting->step_x = 1;
	else
		data->raycasting->step_x = -1;
	if (sin(ray_angle) > 0)
		data->raycasting->step_y = 1;
	else
		data->raycasting->step_y = -1;
	data->raycasting->to_next_cell_x = player->x;
	data->raycasting->to_next_cell_y = player->y;
	display_cells(data->raycasting, delta_x, delta_y, data->cub->map->map_copy);
}

static void	raycast_bis(t_data *data)
{
	double	ray_angle;
	double	cam_angle;
	
	
	cam_angle = data->player->angle;
	while (data->raycasting->count_ray++ < WIN_WIDTH)
	{
		ray_angle = cam_angle - (FOV / 2) + \
		(data->raycasting->count_ray * FOV / WIN_WIDTH);
		send_rays(data, data->player, ray_angle);
	}
}

void	raycast(t_data *data)
{
	init_visited(data->raycasting, data->cub->map->map_copy);
	data->raycasting->data = data;
	data->raycasting->count_ray = -1;
	data->raycasting->angle = data->player->angle;
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
