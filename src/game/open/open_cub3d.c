/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:17 by sperron           #+#    #+#             */
/*   Updated: 2024/11/26 14:17:39 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_cub3d(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		close_all(data, "MLX Init error");
	add_ptr(data->trash_ptr, data->mlx->mlx);
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_WIDTH, \
	WIN_HEIGHT, "Cub3D");
	data->cub->texture[NORTH].img = mlx_xpm_file_to_image(data->mlx->mlx, \
	data->cub->texture[NORTH].path, &data->cub->texture[NORTH].width, \
	&data->cub->texture[NORTH].height);
	data->cub->texture[SOUTH].img = mlx_xpm_file_to_image(data->mlx->mlx, \
	data->cub->texture[SOUTH].path, &data->cub->texture[SOUTH].width, \
	&data->cub->texture[SOUTH].height);
	data->cub->texture[EAST].img = mlx_xpm_file_to_image(data->mlx->mlx, \
	data->cub->texture[EAST].path, &data->cub->texture[EAST].width, \
	&data->cub->texture[EAST].height);
	data->cub->texture[WEST].img = mlx_xpm_file_to_image(data->mlx->mlx, \
	data->cub->texture[WEST].path, &data->cub->texture[WEST].width, \
	&data->cub->texture[WEST].height);
	if (!data->mlx->win)
		close_all(data, "MLX New window error");
	cub3d(data);
}
