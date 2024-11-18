/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:13:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 12:13:16 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_dir(char *path)
{
	char	buf[1];
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	if (read(fd, buf, 1) == -1)
		return (close(fd), 1);
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
		if (!holder)
			break ;
		line = ft_strjoin(holder_map, holder);
		free(holder_map);
		free(holder);
		holder_map = line;
		data->cub->height++;
		if (!holder_map)
			return (NULL);
	}
	return (holder_map);
}

char	**read_cub(char *av, t_data *data)
{
	int		fd;
	char	*holder_map;
	char	**map;

	fd = open(av, O_RDONLY);
	if (is_dir(av) == 1)
		return (clear_all(data),ft_dprintf(2, \
		"Error\nCan't open file %s\n", av), exit(1), NULL);
	add_fd(data->trash_fds, fd);
	holder_map = accumulate_lines(fd, data);
	add_ptr(data->trash_ptr, holder_map);
	if (!holder_map)
		return (clear_all(data), ft_dprintf(2, "Error\nMalloc error\n"), \
		exit(1), NULL);
	map = ft_split(holder_map, '\n');
	add_ptr_tab(data->trash_ptr, (void **)map, data->cub->height, true);
	if (!map || !map[0] || map[0][0] == '\0')
		return (ft_dprintf(2, "Error\nEmpty map\n"), exit(1), NULL);
	remove_ptr(data->trash_ptr, holder_map);
	return (map);
}

int	set_cub(t_data *data, char *av)
{
	data->cub->file = read_cub(av, data);
	return (0);
}