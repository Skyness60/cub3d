/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/27 14:26:42 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	correct_angle(double angle)
{
	if (angle <= 0)
		return (angle += 2 * PI);
	else if (angle > 2 * PI)
		return (angle -= 2 * PI);
	return (angle);
}

static int	send_rays(t_raycast *raycast)
{
	raycast->wall_x = floor(raycast->pos_x);
	raycast->wall_y = floor(raycast->pos_y);
	int i = 0;
	while (1)
	{
		if (raycast->len_x < raycast->len_y)
		{
			raycast->wall_x += raycast->dir_x;
			if (raycast->map[raycast->wall_y][raycast->wall_x] == '1')
				return (1);
			raycast->len_x += raycast->delta_x;
		}
		else
		{
			raycast->wall_y += raycast->dir_y;
			if (raycast->map[raycast->wall_y][raycast->wall_x] == '1')
				return (2);
			raycast->len_y += raycast->delta_y;
		}
		i++;
	}
	return (0);
}

static double	get_start_len(double pos, double dir)
{
	if (floor(pos) == 0)
		return (1);
	else if (dir == -1)
		return (pos - floor(pos));
	else
		return (1 - (pos - floor(pos)));
}

static void	set_data_rays(t_raycast *raycast)
{
	raycast->delta_x = 1 / fabs(cos(raycast->angle));
	raycast->delta_y = 1 / fabs(sin(raycast->angle));
	// printf("delta_x = %f\n", raycast->delta_x);
	// printf("delta_y = %f\n", raycast->delta_y);
	if (raycast->angle < PI)
		raycast->dir_y = -1;
	else
		raycast->dir_y = -1;
	if (raycast->angle < PI / 2 || raycast->angle > PI + PI / 2)
		raycast->dir_x = 1;
	else
		raycast->dir_x = -1;
	// printf("dir_x = %d\n", raycast->dir_x);
	// printf("dir_y = %d\n", raycast->dir_y);
	raycast->len_x = raycast->delta_x * get_start_len(raycast->pos_x, \
	raycast->dir_x); 
	raycast->len_y = raycast->delta_y * get_start_len(raycast->pos_y, \
	raycast->dir_y); 
	// printf("len_x = %f\n", raycast->len_x);
	// printf("len_y = %f\n", raycast->len_y);
	
}

void	raycasting(t_data *data, t_player *player)
{
	t_raycast	raycast;
	int			i;
	
	i = -1;
	raycast.data = data;
	raycast.angle = correct_angle(player->angle + PI / 6);
	raycast.map = data->cub->map->map_copy;
	while (++i < WIN_WIDTH)
	{
		raycast.pos_x = player->x;
		raycast.pos_y = player->y;
		raycast.angle -= FOV / WIN_WIDTH;
		if (i == 500)
			printf("angle du 500 eme rayon : %f\n", raycast.angle);
		else if (i == 501)
			printf("angle du 501 eme rayon : %f\n", raycast.angle);
		raycast.angle = correct_angle(raycast.angle);
		set_data_rays(&raycast);
		if (send_rays(&raycast) == 1)
			display_walls(&raycast, 1, i);
		else
			display_walls(&raycast, 0, i);
	}
}
