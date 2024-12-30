/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:21:28 by sperron           #+#    #+#             */
/*   Updated: 2024/12/30 11:29:26 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_move(t_data *data)
{
	mlx_key_hook(data->mlx->win, handle_move_keypress, data);
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
