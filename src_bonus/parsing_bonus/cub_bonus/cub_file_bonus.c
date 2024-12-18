/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:23:11 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 16:15:59 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_dir(char *path)
{
	char	buf[1];
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	if (read(fd, buf, 1) == -1)
		return (close(fd), 2);
	return (close(fd), 0);
}

static char	*accumulate_lines(int fd, t_data *data)
{
	char	*line;
	char	*holder;
	char	*holder_map;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	holder_map = ft_strdup(line);
	if (!holder_map)
		return (free(line), NULL);
	free(line);
	while (true)
	{
		holder = get_next_line(fd);
		data->cub->height++;
		if (!holder)
			break ;
		line = ft_strjoin(holder_map, holder);
		free(holder_map);
		free(holder);
		holder_map = line;
		if (!holder_map)
			return (NULL);
	}
	return (data->cub->file_without_split = holder_map, holder_map);
}

char	**read_cub(char *av, t_data *data)
{
	int		fd;
	char	*holder_map;
	char	**map;

	fd = open(av, O_RDONLY);
	add_fd(data->trash_fds, fd);
	if (is_dir(av) == 1)
		return (clear_all(data), ft_dprintf(2, \
		"Error\nCan't open file %s\n", av), exit(1), NULL);
	else if (is_dir(av) == 2)
		return (clear_all(data), ft_dprintf(2, \
		"Error\nCan't open directory %s\n", av), exit(1), NULL);
	holder_map = accumulate_lines(fd, data);
	add_ptr(data->trash_ptr, holder_map);
	if (!holder_map)
		return (close_all(data, "Malloc Error"), NULL);
	map = ft_split(holder_map, "\n");
	data->cub->height = ft_tablen(map);
	add_ptr_tab(data->trash_ptr, (void **)map, data->cub->height, true);
	if (!map || !map[0] || map[0][0] == '\0')
		return (close_all(data, "Empty File"), NULL);
	return (map);
}
