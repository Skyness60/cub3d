/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:25:35 by sperron           #+#    #+#             */
/*   Updated: 2024/11/19 13:17:43 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			return (clear_all(data), \
			ft_dprintf(2, "Error\nDuplicate texture\n"), exit(1));
		texture->path = ft_strdup(tab[i + 1]);
		if (!texture->path)
			return (clear_all(data), \
			ft_dprintf(2, "Error\nMalloc error\n"), exit(1));
		add_ptr(data->trash_ptr, texture->path);
	}
}

static void	get_texture(t_data *data, char *line)
{
	char	**tab;
	int		i;

	tab = ft_split(line, " \t\n\v\f");
	if (!tab)
		return (clear_all(data), \
		ft_dprintf(2, "Error\nMalloc error\n"), exit(1));
	add_ptr_tab(data->trash_ptr, (void **)tab, ft_tablen(tab), true);
	i = -1;
	while (tab[++i])
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
	int		i;
	int		j;

	i = -1;
	while (file[++i])
	{
		get_texture(data, file[i]);
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] == 'F')
				check_color(data, file, i, true);
			else if (file[i][j] == 'C')
				check_color(data, file, i, false);
		}
	}
	if (!data->cub->texture[NORTH].path || !data->cub->texture[SOUTH].path || \
		!data->cub->texture[WEST].path || !data->cub->texture[EAST].path)
		return (clear_all(data), \
		ft_dprintf(2, "Error\nMissing texture path\n"), exit(1));
	if (data->cub->char_ceiling[0] == '\0' || data->cub->char_floor[0] == '\0')
		return (clear_all(data), \
		ft_dprintf(2, "Error\nMissing color\n"), exit(1));
}
