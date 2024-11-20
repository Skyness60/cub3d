/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:17 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 15:57:26 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_cub3d(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		close_all(data, "MLX Init error");
	add_ptr(data->trash_ptr, data->mlx->mlx);
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->mlx->win)
		close_all(data, "MLX New window error");
	mlx_hook(data->mlx->win, 17, 0, handle_close, data);
	mlx_key_hook(data->mlx->win, handle_close_keypress, data);
	mlx_loop(data->mlx->mlx);
}
