/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:09 by sperron           #+#    #+#             */
/*   Updated: 2024/11/27 12:51:08 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d(t_data *data, t_player *player)
{
	char	**map;
	map = data->cub->map->map_copy;

	printf("position du joueur : %c\n", map[(int)player->y][(int)player->x]);
	int	i;
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	if (map[(int)player->y][(int)player->x] == 'S')
		player->angle = PI + PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'N')
		player->angle = PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'W')
		player->angle = PI;
	else if (map[(int)player->y][(int)player->x] == 'E')
		player->angle = 2 * PI;
	else
		player->angle = PI / 2;
	printf("angle du joueur : %f\n", player->angle);
	raycasting(data, data->player);
	// handle_close(data);
	// handle_move(data);
	// mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->cub->texture[NORTH].img, 1800, 900);
	mlx_loop(data->mlx->mlx);
	free_all(data->raycast_trash);
	return (0);
}