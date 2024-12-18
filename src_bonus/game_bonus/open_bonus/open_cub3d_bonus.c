/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub3d_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:17 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 18:10:06 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_img_info(t_texture *img, t_data *data)
{
	img->img = mlx_xpm_file_to_image(data->mlx->mlx, img->path, &img->width, \
	&img->height);
	img->buffer = (int*)mlx_get_data_addr(img->img, &img->bpp, &img->sizeline,\
	&img->endian);
}

void	open_cub3d(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		close_all(data, "MLX Init error");
	add_ptr(data->trash_ptr, data->mlx->mlx);
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_WIDTH, \
	WIN_HEIGHT, "Cub3D");
	if (!data->mlx->win)
		close_all(data, "MLX New window error");
	get_img_info(&(data->cub->texture[NORTH]), data);
	get_img_info(&(data->cub->texture[SOUTH]), data);
	get_img_info(&(data->cub->texture[EAST]), data);
	get_img_info(&(data->cub->texture[WEST]), data);
	cub3d(data, data->player);
}
