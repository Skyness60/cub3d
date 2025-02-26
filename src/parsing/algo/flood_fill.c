/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:49:14 by sperron           #+#    #+#             */
/*   Updated: 2025/01/03 11:52:19 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ff(t_data *data, int x, int y, int height)
{
	if (!data->cub->map->map_copy[y][x] || x < 0 || y < 0 \
	|| x >= (int)ft_strlen(data->cub->map->map_copy[y]) \
	|| y >= height || data->cub->map->map_copy[y][x] == '1' \
	|| data->cub->map->map_copy[y][x] == 'X')
		return ;
	if (data->cub->map->map_copy[y][x] == ' ')
		return (close_all(data, "Map not closed: hole in the map"));
	if ((x == 0 || y == 0 || x == data->cub->map->width - 1 \
	|| y == height - 1) && (data->cub->map->map_copy[y][x] == '0'))
		return (close_all(data, "Map not closed: hole on the border"));
	if (y > 0 && data->cub->map->map_copy[y - 1][x] != '1' \
	&& data->cub->map->map_copy[y - 1][x] != 'X' \
	&& data->cub->map->map_copy[y - 1][x] != '0')
		close_all(data, "Map not closed: hole above");
	if (y < height - 1 && data->cub->map->map_copy[y + 1][x] != '1' \
	&& data->cub->map->map_copy[y + 1][x] != 'X' \
	&& data->cub->map->map_copy[y + 1][x] != '0')
		close_all(data, "Map not closed: hole below");
	data->cub->map->map_copy[y][x] = 'X';
	return (ff(data, x + 1, y, height), ff(data, x - 1, y, height), \
	ff(data, x, y - 1, height), ff(data, x, y + 1, height), \
	ff(data, x + 1, y + 1, height), ff(data, x - 1, y - 1, height), \
	ff(data, x + 1, y - 1, height), ff(data, x - 1, y + 1, height));
}

void	ft_to_fill(t_data *data, int move_x, int move_y, int height)
{
	ff(data, move_x, move_y, height);
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
				data->player->x = (double)j + 0.01;
				data->player->y = (double)i + 0.01;
				if (i == 0 || i == data->cub->map->height - 1 \
				|| j == 0 || j == (int)ft_strlen(m[i]) - 1)
					return (close_all(data, "Wrong player position border"));
				if ((int)data->player->x > (int)ft_strlen(m[i - 1]) \
				|| (int)data->player->x > (int)ft_strlen(m[i + 1]))
					return (close_all(data, "Wrong player position"));
				return ;
			}
			j++;
		}
		i++;
	}
}

void	diagona_check(t_data *data)
{
	int	i;
	int	len;

	i = -1;
	while (++i < data->cub->map->height)
	{
		len = ft_strlen(data->cub->map->map[i]);
		data->cub->map->map_copy[i] = malloc(len + 2);
		if (!data->cub->map->map_copy[i])
			close_all(data, "Malloc error");
		ft_strlcpy(data->cub->map->map_copy[i], \
		data->cub->map->map[i], len + 3);
		data->cub->map->map_copy[i][len] = '0';
		data->cub->map->map_copy[i][len + 1] = '\0';
	}
	data->cub->map->width += 1;
	add_ptr_tab(data->trash_ptr, (void *)data->cub->map->map_copy, \
	data->cub->map->height, true);
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
	data->cub->map->width += 2;
	add_ptr_tab(data->trash_ptr, \
	(void *)data->cub->map->map_copy, data->cub->map->height, true);
	diagona_check(data);
	ft_player_position(data->cub->map->map_copy, data, \
	data->player->orientation);
	ft_to_fill(data, data->player->x, data->player->y, \
	data->cub->map->height);
	return (0);
}
