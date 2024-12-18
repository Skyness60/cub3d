/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move_debug.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/11/22 17:28:15 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_debug_move(t_data *data)
{
	printf("Player Position: x = %.2f, y = %.2f, angle = %.2f\n", 
		data->player->x, 
		data->player->y, 
		data->player->angle);
}

void	print_map_with_player(t_data *data)
{
	int	y;
	int	x;

	printf("\nMap:\n");
	for (y = 0; data->cub->map->map[y]; y++)
	{
		for (x = 0; data->cub->map->map[y][x]; x++)
		{
			if ((int)data->player->y == y && (int)data->player->x == x)
				printf("P"); // Représente la position du joueur
			else
				printf("%c", data->cub->map->map[y][x]);
		}
		printf("\n");
	}
}