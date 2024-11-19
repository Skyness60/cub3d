/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:13:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/19 13:13:04 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_cub(t_data *data, char *av)
{
	int	i;

	i = -1;
	data->cub->file = read_cub(av, data);
	read_map(data->cub->file, data);
	read_texture(data->cub->file, data);
	while (++i < 4)
		if (check_xpm(data->cub->texture[i].path))
			return (clear_all(data), \
			ft_dprintf(2, "Error\nWrong texture extension\n"), exit(1), 1);
	//checker_map(data);
	return (0);
}
