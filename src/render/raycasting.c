/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:46:19 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/13 16:29:00 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_exact_hit(t_raycast *raycast)
{
	if (raycast->x == 1)
	{
		raycast->precise_hit = raycast->len_x * fabs(cos(raycast->angle)) + \
		raycast->player->x;
		raycast->precise_hit -= (int)raycast->precise_hit;
	}
	else
	{
		raycast->precise_hit = raycast->len_y * fabs(sin(raycast->angle)) + \
		raycast->player->y;
		raycast->precise_hit -= (int)raycast->precise_hit;	
	}
}

static bool	get_distances(t_raycast *raycast)
{
	raycast->pos_x = (int)raycast->player->x + raycast->step_y;
	raycast->pos_y = (int)raycast->player->y + raycast->step_y;
	raycast->len_x = raycast->delta_x * (raycast->player->x - \
	(int)raycast->player->x);
	raycast->len_y = raycast->delta_y * (raycast->player->y - \
	(int)raycast->player->y);
	while (1)
	{
		if (raycast->len_x < raycast->len_y)
		{
			if (raycast->data->cub->map->map[raycast->pos_y][raycast->pos_x] \
			== '1')
				return (1);
			raycast->len_x += raycast->delta_x;
			raycast->pos_x += raycast->step_x;
		}
		else
		{
			if (raycast->data->cub->map->map[raycast->pos_y][raycast->pos_x] \
			== '1')
				return (0);
			raycast->len_x += raycast->delta_x;
			raycast->pos_x += raycast->step_x;
		}
	} 
}

static void	get_directions(t_raycast *raycast)
{
	if (raycast->angle > PI / 2 && raycast->angle < PI + PI / 2)
		raycast->step_x = -1;
	else
		raycast->step_x = 1;
	if (raycast->angle > PI)
		raycast->step_y = 1;
	else
		raycast->step_y = -1;
	
}

void	raycasting(t_data *data, t_player *player)
{
	t_raycast	raycast;

	data->raycast = &raycast;
	raycast.angle = player->angle - FOV / 2;
	raycast.count_r = 0;
	raycast.data = data;
	raycast.player = player;
	while (raycast.count_r < WIN_WIDTH)
	{
		raycast.angle += 1 / WIN_WIDTH / FOV;
		if (raycast.angle >= 2 * PI)
			raycast.angle -= 2 * PI;	
		raycast.delta_x = fabs(1 / cos(raycast.angle));
		raycast.delta_y = fabs(1 / sin(raycast.angle));
		get_directions(&raycast);
		raycast.x = get_distances(&raycast);
		get_exact_hit(&raycast);
		construct_img(data, &raycast);
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, \
	raycast.new_img, 0, 0);
}
