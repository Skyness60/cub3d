/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:53:59 by sperron           #+#    #+#             */
/*   Updated: 2024/11/22 16:47:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_close_icon(t_data *data)
{
	ft_dprintf(1, "Cub3D closed\n");
	if (data->mlx->win != NULL)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx != NULL)
		mlx_destroy_display(data->mlx->mlx);
	clear_all(data);
	exit(0);
	return (0);
}

static int	handle_close_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_close_icon(data);
	return (0);
}

void	handle_close(t_data *data)
{
	mlx_hook(data->mlx->win, 17, 0, handle_close_icon, data);
	mlx_hook(data->mlx->win, 2, 1L << 0, handle_close_keypress, data);
}
