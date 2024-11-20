/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:00:04 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 16:19:52 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_map(t_data *data)
{
	size_t	i;

	i = -1;
	printf("=== Data Stats ===\n");
	debug_gc(data->trash_ptr);
	printf("=== Map Stats ===\n");
	printf("Largeur : %d\n", data->cub->map->width);
	printf("Hauteur : %d\n", data->cub->map->height);
	printf("Map:\n");
	while (++i < data->cub->map->height)
		printf("%s\n", data->cub->map->map[i]);
	printf("=== Texture Stats ===\n");
	printf("NO : %s\n", data->cub->texture[0].path);
	printf("SO : %s\n", data->cub->texture[1].path);
	printf("WE : %s\n", data->cub->texture[2].path);
	printf("EA : %s\n", data->cub->texture[3].path);
	printf("=== Color Stats ===\n");
	printf("Plafond : %s\n", data->cub->char_ceiling);
	printf("Sol : %s\n", data->cub->char_floor);
	printf("================================\n");
}
