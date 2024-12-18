/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:20:58 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 16:21:08 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
# define RS 0.1 

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

int handle_mouse_move(t_data *data)
{
    double tmp;
    double tmp_plane;
    float rs;
    int x;
    int y;
    int mouse_offset;

    mlx_mouse_get_pos(data->mlx->mlx, data->mlx->win, &x, &y);
    mouse_offset = x - WIN_WIDTH / 2;
    rs = (RS / 50.0) * (float)mouse_offset;
    tmp = data->player->angle;
    tmp_plane = data->player->orientation;
    data->player->angle += rs;
    if (data->player->angle > 2 * PI)
        data->player->angle -= 2 * PI;
    else if (data->player->angle < 0)
        data->player->angle += 2 * PI;
    data->player->orientation = tmp * cos(rs) - tmp_plane * sin(rs);
    tmp_plane = tmp * sin(rs) + tmp_plane * cos(rs);
    mlx_mouse_move(data->mlx->mlx, data->mlx->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
    return (0);
}

