/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:09 by sperron           #+#    #+#             */
/*   Updated: 2024/12/14 19:14:05 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d(t_data *data, t_player *player)
{
	if (data->cub->map->map[(int)player->y][(int)player->x] == 'S')
		player->angle = PI + PI / 2;
	else if (data->cub->map->map[(int)player->y][(int)player->x] == 'N')
		player->angle = PI / 2;
	else if (data->cub->map->map[(int)player->y][(int)player->x] == 'W')
		player->angle = PI;
	else if (data->cub->map->map[(int)player->y][(int)player->x] == 'E')
		player->angle = 2 * PI;

	// handle_close(data);
	// mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->cub->texture[NORTH].img, 1800, 900);
	//handle_move(data);
	raycasting(data, data->player);
	mlx_loop(data->mlx->mlx);
	free_all(data->raycast_trash);

	return (0);
}