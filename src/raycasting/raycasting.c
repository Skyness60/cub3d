/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/26 14:18:15 by jlebard          ###   ########.fr       */
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

static void	*display_cells(t_raycasting *raycasting, double delta_x,
						double delta_y,	t_map *map)
{	
	raycasting->to_next_cell_x = ((int)raycasting->x - raycasting->x) / delta_x;
	raycasting->to_next_cell_y = ((int)raycasting->y - raycasting->y) / delta_y;
	while (1)
	{
		if (raycasting->to_next_cell_x < raycasting->to_next_cell_y)
		{
			raycasting->x += raycasting->step_x;
			raycasting->to_next_cell_x += delta_x;
			if (map->map_copy[(int)raycasting->y][(int)raycasting->x] == '1')
				return (display_cells_bis(raycasting->to_next_cell_x, \
				1, raycasting),	NULL);
		}
		else
		{
			raycasting->y += raycasting->step_y;	
			raycasting->to_next_cell_y += delta_y;
			if (map->map_copy[(int)raycasting->y][(int)raycasting->x] == '1')
				return (display_cells_bis(raycasting->to_next_cell_y, \
				0, raycasting),	NULL);
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
	display_cells(data->raycasting, delta_x, delta_y, data->cub->map);
}

static void	raycast_bis(t_data *data)
{
	double	ray_angle;
	double	cam_angle;
	
	
	cam_angle = data->player->angle;
	while (data->raycasting->count_ray++ < WIN_WIDTH)
	{
		data->raycasting->x = data->player->x;
		data->raycasting->y = data->player->y;
		ray_angle = cam_angle - (FOV / 2) + \
		(data->raycasting->count_ray * FOV / WIN_WIDTH);
		send_rays(data, data->player, ray_angle);
	}
}

int	raycast(t_data *data)
{
	data->raycast_trash = malloc(sizeof(t_garb_c));
	init_garbage_collector(data->raycast_trash);
	data->raycasting->data = data;
	init_visited(data->raycasting, data->cub->map->map_copy);
	data->raycasting->count_ray = -1;
	if (data->player->spawn == 1)
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
			data->player->spawn = 0;
		}
	}
	data->raycasting->angle = data->player->angle;
	raycast_bis(data);
	free_all(data->raycast_trash);
	free(data->raycast_trash);
	return (0);
}
