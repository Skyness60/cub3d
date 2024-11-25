/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:20:58 by sperron           #+#    #+#             */
/*   Updated: 2024/11/25 13:22:06 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x + data->player->speed * cos(data->player->angle);
	new_y = data->player->y + data->player->speed * sin(data->player->angle);
	if (data->cub->map->map[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

static void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x - data->player->speed * cos(data->player->angle);
	new_y = data->player->y - data->player->speed * sin(data->player->angle);
	if (data->cub->map->map[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

static void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x - data->player->speed * sin(data->player->angle);
	new_y = data->player->y + data->player->speed * cos(data->player->angle);
	if (data->cub->map->map[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

static void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x + data->player->speed * sin(data->player->angle);
	new_y = data->player->y - data->player->speed * cos(data->player->angle);
	if (data->cub->map->map[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

int	handle_move_keypress(int keycode, t_data *data)
{
	if (keycode == XK_w)
		move_forward(data);
	else if (keycode == XK_s)
		move_backward(data);
	else if (keycode == XK_a)
		move_left(data);
	else if (keycode == XK_d)
		move_right(data);
	else if (keycode == XK_Left)
		data->player->angle -= 0.1;
	else if (keycode == XK_Right)
		data->player->angle += 0.1;
	data->player->angle = fmod(data->player->angle, 2 * PI);
	if (data->player->angle < 0)
		data->player->angle += 2 * PI;
	handle_debug_move(data);
	print_map_with_player(data);
	return (0);
}

