/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:09 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 17:12:10 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d_loop(t_data *data)
{
	handle_move_keypress(data);
	raycasting(data, data->player);
	return (0);
}

static void setup_hook(t_data *data)
{
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, handle_keyrelease, data);
	handle_close(data);
}

int	cub3d(t_data *data, t_player *player)
{
	char	**map;
	map = data->cub->map->map;	
	if (map[(int)player->y][(int)player->x] == 'N')
		player->angle = PI + PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'S')
		player->angle = PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'W')
		player->angle = PI;
	else if (map[(int)player->y][(int)player->x] == 'E')
		player->angle = 2 * PI;
	player->angle += 0.001;
	setup_hook(data);
	mlx_loop_hook(data->mlx->mlx, cub3d_loop, data);
	mlx_loop(data->mlx->mlx);
	free_all(data->raycast_trash);
	return (0);
}