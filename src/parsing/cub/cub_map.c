/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:53:19 by sperron           #+#    #+#             */
/*   Updated: 2024/12/31 14:42:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	expand_map_capacity(t_data *data, int *map_capacity)
{
	char	**new_map;
	int		k;

	*map_capacity *= 2;
	new_map = malloc(*map_capacity * sizeof(char *));
	if (!new_map)
		return (close_all(data, "Malloc error"));
	k = -1;
	while (++k < data->cub->map->height)
		new_map[k] = data->cub->map->map[k];
	remove_ptr(data->trash_ptr, data->cub->map->map);
	data->cub->map->map = new_map;
	add_ptr(data->trash_ptr, new_map);
}

bool	is_line_valid(char *line)
{
	int	j;

	j = -1;
	if (ft_strlen(line) < 3)
		return (false);
	while (line[++j] != '\0')
	{
		if (line[j] != 'E' && line[j] != 'C' && line[j] != '0' \
			&& line[j] != '1' && line[j] != 'N' && line[j] != 'S' \
			&& line[j] != 'W' && !ft_isspace(line[j]))
			return (false);
	}
	return (true);
}

bool	is_map_start(char *line)
{
	int	j;

	j = -1;
	while (line[++j] != '\0')
	{
		if (!ft_isspace(line[j]) && is_line_valid(line) && line[j] == '1')
			return (true);
	}
	return (false);
}

void	add_map_line(t_data *data, char *line, int *map_capacity)
{
	if (data->cub->map->height >= *map_capacity)
		expand_map_capacity(data, map_capacity);
	data->cub->map->map[data->cub->map->height] = ft_strdup(line);
	if (!data->cub->map->map[data->cub->map->height])
		return (close_all(data, "Malloc error"));
	add_ptr(data->trash_ptr, data->cub->map->map[data->cub->map->height]);
	if (data->cub->map->width < (int) ft_strlen(line))
		data->cub->map->width = ft_strlen(line);
	data->cub->map->height++;
}

void	read_map(char **file, t_data *data)
{
	int		i;
	int		map_capacity;
	bool	in_map;

	i = -1;
	in_map = false;
	map_capacity = 10;
	data->cub->map->map = malloc(map_capacity * sizeof(char *));
	if (!data->cub->map->map)
		return ;
	add_ptr(data->trash_ptr, data->cub->map->map);
	data->cub->map->height = 0;
	data->cub->map->width = 0;
	while (file[++i])
	{
		if (!in_map && is_map_start(file[i]))
			in_map = true;
		if (in_map)
		{
			add_map_line(data, file[i], &map_capacity);
			if (!is_line_valid(file[i]) || check_empty_line(data) == true)
				return (close_all(data, "Invalid map"));
		}
	}
}
