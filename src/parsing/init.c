/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:37 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 10:57:42 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	allocate_memory(void **ptr, size_t size, const char *err_msg)
{
	*ptr = malloc(size);
	if (!*ptr)
	{
		ft_dprintf(2, "%s\n", err_msg);
		exit(1);
	}
}

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
}

static void	init_texture(t_texture *texture, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		texture[i].path = NULL;
		texture[i].img = NULL;
		texture[i].data = NULL;
		texture[i].width = 0;
		texture[i].height = 0;
		i++;
	}
}

static void	init_trash_pointers(t_data *data)
{
	add_ptr(data->trash_ptr, data->map);
	add_ptr(data->trash_ptr, data->texture);
}

void	init_data(t_data **data_ptr)
{
	t_data	*data;

	data = NULL;
	allocate_memory((void **)data_ptr, sizeof(t_data), "Malloc error for t_data");
	data = *data_ptr;
	allocate_memory((void **)&data->map, sizeof(t_map), "Malloc error for t_map");
	init_map(data->map);
	allocate_memory((void **)&data->texture, sizeof(t_texture) * 4, "Malloc error for t_texture");
	init_texture(data->texture, 4);
	allocate_memory((void **)&data->trash_ptr, sizeof(t_garb_c), "Malloc error for trash_ptr");
	init_garbage_collector(data->trash_ptr);
	allocate_memory((void **)&data->trash_fds, sizeof(t_garb_d), \
	"Malloc error for trash_fds");
	init_garbage_descriptor(data->trash_fds);
	init_trash_pointers(data);
}
