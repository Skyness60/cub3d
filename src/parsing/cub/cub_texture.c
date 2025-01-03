/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:25:35 by sperron           #+#    #+#             */
/*   Updated: 2024/12/31 15:38:11 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(t_data *data, t_texture *texture)
{
	int		fd;
	char	buff;

	fd = open(texture->path, O_RDONLY);
	if (fd < 0)
		return (close_all(data, "Texture file not found"));
	add_fd(data->trash_fds, fd);
	if (read(fd, &buff, 1) < 0)
		return (close_all(data, "Texture not readable"));
}

void	check_orientation(t_data *data, char **tab, int i)
{
	t_texture	*texture;

	texture = NULL;
	if (tab[i][0] == 'N' && tab[i][1] == 'O')
		texture = &data->cub->texture[NORTH];
	else if (tab[i][0] == 'S' && tab[i][1] == 'O')
		texture = &data->cub->texture[SOUTH];
	else if (tab[i][0] == 'W' && tab[i][1] == 'E')
		texture = &data->cub->texture[WEST];
	else if (tab[i][0] == 'E' && tab[i][1] == 'A')
		texture = &data->cub->texture[EAST];
	if (texture)
	{
		if (texture->path)
			return (close_all(data, "Duplicate texture"));
		texture->path = ft_strdup(tab[i + 1]);
		if (!texture->path)
			return (close_all(data, "Malloc error"));
		add_ptr(data->trash_ptr, texture->path);
		check_file(data, texture);
	}
}

static void	get_texture(t_data *data, char *line)
{
	char	**tab;
	int		i;

	tab = ft_split(line, " \t\n\v\f");
	if (!tab)
		return (close_all(data, "Malloc error"));
	add_ptr_tab(data->trash_ptr, (void **)tab, ft_tablen(tab), true);
	i = -1;
	while (tab[++i] && ft_tablen(tab) > 1)
	{
		check_orientation(data, tab, i);
	}
	i = -1;
	while (tab[++i])
		remove_ptr(data->trash_ptr, tab[i]);
	remove_ptr(data->trash_ptr, tab);
}

void	read_texture(char **file, t_data *data)
{
	if (file[0][0] == 'N' && file[0][1] == 'O')
		get_texture(data, file[0]);
	if (file[1][0] == 'S' && file[1][1] == 'O')
		get_texture(data, file[1]);
	if (file[2][0] == 'W' && file[2][1] == 'E')
		get_texture(data, file[2]);
	if (file[3][0] == 'E' && file[3][1] == 'A')
		get_texture(data, file[3]);
	if (file[4][0] == 'F' && file[4][1] == ' ')
		check_color(data, file, 4, true);
	if (file[5][0] == 'C' && file[5][1] == ' ')
		check_color(data, file, 5, false);
	if (!data->cub->texture[NORTH].path \
	|| !data->cub->texture[SOUTH].path \
	|| !data->cub->texture[WEST].path \
	|| !data->cub->texture[EAST].path)
		return (close_all(data, "Texture incorrect"));
	if (data->cub->char_ceiling[0] == '\0' \
	|| data->cub->char_floor[0] == '\0')
		return (close_all(data, "Color incorrect"));
	if (ft_strncmp(file[6], data->cub->map->map[0], \
	ft_strlen(data->cub->map->map[0])))
		return (close_all(data, "Cub file incorrect"));
}
