/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:37 by sperron           #+#    #+#             */
/*   Updated: 2024/11/19 15:29:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	allocate_memory(void **ptr, size_t size, char *err_msg, t_data *d)
{
	*ptr = malloc(size);
	if (!*ptr)
		close_all(d, err_msg);
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

static void	init_cub(t_cub *cub, t_data *data)
{
	cub->file = NULL;
	cub->file_without_split = NULL;
	cub->texture = NULL;
	cub->height = 1;
	cub->width = 0;
	cub->map = NULL;
	cub->hex_ceiling = 0;
	cub->hex_floor = 0;
	cub->char_ceiling = ft_strdup("");
	add_ptr(data->trash_ptr, cub->char_ceiling);
	cub->char_floor = ft_strdup("");
	add_ptr(data->trash_ptr, cub->char_floor);
	allocate_memory((void **)&cub->texture, \
	sizeof(t_texture) * 4, "Malloc error for t_texture", data);
	init_texture(cub->texture, 4);
	add_ptr(data->trash_ptr, cub->texture);
	allocate_memory((void **)&cub->map, sizeof(t_map), \
	"Malloc error for t_map", data);
	add_ptr(data->trash_ptr, cub->map);
}

void	init_data(t_data **data_ptr)
{
	t_data	*data;

	data = NULL;
	allocate_memory((void **)data_ptr, sizeof(t_data), \
	"Malloc error for t_data", data);
	data = *data_ptr;
	allocate_memory((void **)&data->trash_ptr, sizeof(t_garb_c), \
	"Malloc error for trash_ptr", data);
	init_garbage_collector(data->trash_ptr);
	allocate_memory((void **)&data->trash_fds, sizeof(t_garb_d), \
	"Malloc error for trash_fds", data);
	init_garbage_descriptor(data->trash_fds);
	allocate_memory((void **)&data->cub, sizeof(t_cub), \
	"Malloc error for t_cub", data);
	init_cub(data->cub, data);
	add_ptr(data->trash_ptr, data->cub);
	data->look.dirX = 0;
	data->look.dirY = 1;
}
