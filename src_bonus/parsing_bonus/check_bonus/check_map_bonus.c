/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:12:32 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 16:02:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line(char **line, t_data *data)
{
	int	j;
	int	i;

	i = -1;
	while (++i < data->cub->map->height)
	{
		j = -1;
		if (ft_strlen(line[i]) < 3)
			return (false);
		while (line[i][++j] != '\0')
			if (line[i][j] != 'E' && line[i][j] != 'C' && line[i][j] != '0' \
				&& line[i][j] != '1' && line[i][j] != 'N' && line[i][j] != \
				'S' && line[i][j] != 'W' && !ft_isspace(line[i][j]))
				return (false);
	}
	return (true);
}

static bool	check_player(char **map, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->cub->map->height)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == 'N')
				data->player->orientation = 'N';
			else if (map[i][j] == 'S')
				data->player->orientation = 'S';
			else if (map[i][j] == 'W')
				data->player->orientation = 'W';
			else if (map[i][j] == 'E')
				data->player->orientation = 'E';
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' \
				|| map[i][j] == 'E')
				data->player->nb++;
		}
	}
	if (data->player->nb == 0 || data->player->nb > 1)
		return (close_all(data, "Player error"), false);
	return (true);
}

int	check_map(t_data *data)
{
	if (data->cub->map->map && check_line(data->cub->map->map, data) == \
	true && check_player(data->cub->map->map, data) == true && \
	verify_win(data) == false)
		return (ft_dprintf(1, "map valid\n"), false);
	else
		return (close_all(data, "Map error wall not close"), false);
}
