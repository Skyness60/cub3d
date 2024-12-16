/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:20:58 by sperron           #+#    #+#             */
/*   Updated: 2024/12/16 11:06:21 by sperron          ###   ########.fr       */
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

int	handle_move_keypress(t_data *data)
{
	if (data->keys->w)
		move_forward(data);
	else if (data->keys->s)
		move_backward(data);
	else if (data->keys->a)
		move_left(data);
	else if (data->keys->d)
		move_right(data);
	else if (data->keys->left)
		data->player->angle -= 0.1;
	else if (data->keys->right)
		data->player->angle += 0.1;
	//handle_debug_move(data);
	//print_map_with_player(data);
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys->w = true;
	else if (keycode == XK_s)
		data->keys->s = true;
	else if (keycode == XK_a)
		data->keys->a = true;
	else if (keycode == XK_d)
		data->keys->d = true;
	else if (keycode == XK_Left)
		data->keys->left = true;
	else if (keycode == XK_Right)
		data->keys->right = true;
	else if (keycode == XK_Escape)
		handle_close_icon(data);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys->w = false;
	else if (keycode == XK_s)
		data->keys->s = false;
	else if (keycode == XK_a)
		data->keys->a = false;
	else if (keycode == XK_d)
		data->keys->d = false;
	else if (keycode == XK_Left)
		data->keys->left = false;
	else if (keycode == XK_Right)
		data->keys->right = false;
	return (0);
}
