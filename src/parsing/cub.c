/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:13:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 16:51:50 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_cub(t_data *data, char *av)
{
	data->cub->file = read_cub(av, data);
	read_map(data->cub->file, data);
	read_texture(data->cub->file, data);
	return (0);
}
