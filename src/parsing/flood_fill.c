/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:49:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 13:40:30 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	flood_fill(t_data *data, int x, int y, int height)
{
	if (x < 0 || y < 0 || x >= height \
	|| y >= (int)ft_strlen(data->cub->map->map_copy[x]) \
	|| data->cub->map->map_copy[x][y] == '1' \
	|| data->cub->map->map_copy[x][y] == 'X')
		return ;
	if ((x == 0 || y == 0 || x == height - 1 \
	|| y == (int)ft_strlen(data->cub->map->map_copy[x]) - 1) \
	&& (data->cub->map->map_copy[x][y] == '0' \
	|| data->cub->map->map_copy[x][y] == ' '))
		return (close_all(data, "Map not close"));
	data->cub->map->map_copy[x][y] = 'X';
	flood_fill(data, x - 1, y, height);
	flood_fill(data, x + 1, y, height);
	flood_fill(data, x, y - 1, height);
	flood_fill(data, x, y + 1, height);
}

void	ft_to_fill(t_data *data, int move_x, int move_y, int height)
{
	flood_fill(data, move_x, move_y, height);
}

void	ft_player_position(char **m, t_data *data, char p)
{
	int	i;
	int	j;

	i = 0;
	while (m[i])
	{
		j = 0;
		while (m[i][j])
		{
			if (m[i][j] == p)
			{
				data->player->x = i;
				data->player->y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	verify_win(t_data *data)
{
	int	can_row;

	can_row = -1;
	data->cub->map->map_copy = malloc(sizeof(char *) * \
	(data->cub->map->height + 1));
	if (!data->cub->map->map_copy)
		return (close_all(data, "Malloc error"), 0);
	while (++can_row < data->cub->map->height)
	{
		data->cub->map->map_copy[can_row] = \
		ft_strdup(data->cub->map->map[can_row]);
		if (!data->cub->map->map_copy[can_row])
			return (close_all(data, "Malloc error"), 0);
	}
	data->cub->map->map_copy[can_row] = NULL;
	add_ptr_tab(data->trash_ptr, \
	(void *)data->cub->map->map_copy, data->cub->map->height, true);
	ft_player_position(data->cub->map->map_copy, data, \
	data->player->orientation);
	replace_tabs_with_spaces(data->cub->map->map_copy, data);
	ft_to_fill(data, data->player->x, data->player->y, \
	data->cub->map->height);
	return (0);
}
