/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:46:19 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/14 18:23:36 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_exact_hit(t_raycast *raycast)
{
	if (raycast->x == 1)
	{
		raycast->precise_hit = raycast->len_x * fabs(cos(raycast->angle)) + \
		raycast->player->x;
		raycast->precise_hit -= floor(raycast->precise_hit);
	}
	else
	{
		raycast->precise_hit = raycast->len_y * fabs(sin(raycast->angle)) + \
		raycast->player->y;
		raycast->precise_hit -= floor(raycast->precise_hit);
	}
	if (raycast->x && raycast->step_y == -1)
		raycast->precise_hit = 1.0 - raycast->precise_hit;
	if (raycast->x == 0 && raycast->step_x == -1)
		raycast->precise_hit = 1.0 - raycast->precise_hit;
}
static void	get_first_dt(t_raycast *raycast)
{
	double	float_pos_x;
	double	float_pos_y;

	float_pos_x = raycast->player->x - (int)raycast->player->x;
	float_pos_y = raycast->player->y - (int)raycast->player->y;
	if (float_pos_x == 0)
		raycast->len_x += raycast->delta_x;
	else if (raycast->step_x == 1)
		raycast->len_x = (1.0 - float_pos_x) * raycast->delta_x;
	else
		raycast->len_x = float_pos_x * raycast->delta_x;
	if (float_pos_y == 0)
		raycast->len_y += raycast->delta_y;
	else if (raycast->step_x == 1)
		raycast->len_y = (1.0 - float_pos_y) * raycast->delta_y;
	else
		raycast->len_y = float_pos_x * raycast->delta_y;
}


static bool	get_distances(t_raycast *raycast)
{
	raycast->len_x = 0;
	raycast->len_y = 0;
	raycast->pos_x = (int)raycast->player->x;
	raycast->pos_y = (int)raycast->player->y;
	get_first_dt(raycast);
	while (1)
	{
		if (raycast->len_x < raycast->len_y)
		{
			raycast->pos_x += raycast->step_x;
			if (raycast->data->cub->map->map[raycast->pos_y][raycast->pos_x] \
			== '1')
				return (1);
			raycast->len_x += raycast->delta_x;
		}
		else
		{
			raycast->pos_y += raycast->step_y;
			if (raycast->data->cub->map->map[raycast->pos_y][raycast->pos_x] \
			== '1')
				return (0);
			raycast->len_y += raycast->delta_y;
		}
	}
}

static void	get_directions(t_raycast *raycast)
{
	if (raycast->angle > PI / 2 && raycast->angle < 3 * PI / 2)
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
	int	bpp;
	int	sizeline;
	int	endian;
	
	data->raycast = &raycast;
	raycast.angle = player->angle - FOV / 2;
	raycast.count_r = 0;
	raycast.data = data;
	raycast.player = player;
	raycast.new_img = mlx_new_image(data->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	raycast.new_buff = (int *)(mlx_get_data_addr(raycast.new_img, &bpp, &sizeline, &endian));
	while (raycast.count_r < WIN_WIDTH)
	{
		raycast.angle += FOV / WIN_WIDTH;
		if (raycast.angle >= 2 * PI)
			raycast.angle -= 2 * PI;
		raycast.delta_x = fabs(1 / cos(raycast.angle));
		raycast.delta_y = fabs(1 / sin(raycast.angle));
		get_directions(&raycast);
		raycast.x = get_distances(&raycast);
		get_exact_hit(&raycast);
		construct_img(data, &raycast);
		raycast.count_r++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, \
	raycast.new_img, 0, 0);
}
