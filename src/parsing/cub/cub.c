/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:13:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 15:29:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_cub(t_data *data, char *av)
{
	int	i;

	i = -1;
	data->cub->file = read_cub(av, data);
	read_map(data->cub->file, data);
	read_texture(data->cub->file, data);
	while (++i < 4)
		if (check_xpm(data->cub->texture[i].path))
			return (close_all(data, "Wrong texture extension"), 1);
	check_map(data);
	return (0);
}
