/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:03:37 by sperron           #+#    #+#             */
/*   Updated: 2024/12/15 13:26:31 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	init_keys(t_data *data)
{
	allocate_memory((void **)&data->keys, sizeof(t_keys), \
	"Malloc error for t_keys", data);
	data->keys->w = false;
	data->keys->s = false;
	data->keys->a = false;
	data->keys->d = false;
	data->keys->left = false;
	data->keys->right = false;
	add_ptr(data->trash_ptr, data->keys);
}

void	init_data(t_data *data)
{
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
	init_keys(data);
	allocate_memory((void **)&data->player, sizeof(t_player), \
	"Malloc error for t_cub", data);
	add_ptr(data->trash_ptr, data->player);
	allocate_memory((void **)&data->mlx, sizeof(t_mlx), \
	"Malloc error for t_cub", data);
	add_ptr(data->trash_ptr, data->mlx);
	allocate_memory((void **)&data->raycast, sizeof(t_raycast), \
	"Malloc error for t_raycasting", data);
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->player->orientation = '\0';
	data->player->nb = 0;
	data->player->speed = 0.2;
}
