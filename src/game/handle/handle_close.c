/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:53:59 by sperron           #+#    #+#             */
/*   Updated: 2024/12/16 10:39:05 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_close_icon(t_data *data)
{
	ft_dprintf(1, "Cub3D closed\n");
	mlx_destroy_image(data->mlx->mlx, data->cub->texture[NORTH].img);
	mlx_destroy_image(data->mlx->mlx, data->cub->texture[SOUTH].img);
	mlx_destroy_image(data->mlx->mlx, data->cub->texture[EAST].img);
	mlx_destroy_image(data->mlx->mlx, data->cub->texture[WEST].img);
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
