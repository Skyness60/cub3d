/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:20:58 by sperron           #+#    #+#             */
/*   Updated: 2024/12/30 11:29:07 by jlebard          ###   ########.fr       */
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

	new_y = data->player->y - data->player->speed * cos(data->player->angle);
	new_x = data->player->x + data->player->speed * sin(data->player->angle);
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

	new_y = data->player->y + data->player->speed * cos(data->player->angle);
	new_x = data->player->x - data->player->speed * sin(data->player->angle);
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
	if (data->keys->s)
		move_backward(data);
	if (data->keys->a)
		move_left(data);
	if (data->keys->d)
		move_right(data);
	if (data->keys->left)
		data->player->angle -= 0.05;
	if (data->keys->right)
		data->player->angle += 0.05;
	return (0);
}
