/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cub3d_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:09 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 17:11:48 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d_loop(t_data *data)
{
	handle_move_keypress(data);
	handle_mouse_move(data);
	raycasting(data, data->player);
	return (0);
}

static void setup_hook(t_data *data)
{	
    mlx_hook(data->mlx->win, KeyPress, KeyPressMask, handle_keypress, data);
    mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, handle_keyrelease, data);
    handle_close(data);
    mlx_mouse_hide(data->mlx->mlx, data->mlx->win);
}


int	cub3d(t_data *data, t_player *player)
{
	char	**map;
	map = data->cub->map->map;	
	if (map[(int)player->y][(int)player->x] == 'S')
		player->angle = PI + PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'N')
		player->angle = PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'W')
		player->angle = PI;
	else if (map[(int)player->y][(int)player->x] == 'E')
		player->angle = 2 * PI;
	setup_hook(data);
	player->angle += 0.001;
	mlx_loop_hook(data->mlx->mlx, cub3d_loop, data);
	// handle_move(data);
	// handle_close(data);
	// mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->cub->texture[NORTH].img, 1800, 900);
	mlx_loop(data->mlx->mlx);
	free_all(data->raycast_trash);
	return (0);
}