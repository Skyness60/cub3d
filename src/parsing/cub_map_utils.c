/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:19:33 by sperron           #+#    #+#             */
/*   Updated: 2024/11/19 16:37:26 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	check_empty_line(t_data *data)
{
	int		i;
	bool	in_map;

	i = -1;
	in_map = false;
	while (data->cub->file_without_split[++i] != '\0')
	{
		if (in_map == false && data->cub->file_without_split[i] \
		&& data->cub->file_without_split[i + 1] \
		&& data->cub->file_without_split[i + 2] \
		&& data->cub->file_without_split[i] == '1' \
		&& data->cub->file_without_split[i + 1] == '1' && \
		data->cub->file_without_split[i + 2] == '1')
			in_map = true;
		if (in_map == true && data->cub->file_without_split[i] \
		&& data->cub->file_without_split[i + 1] \
		&& data->cub->file_without_split[i] == '\n' \
		&& data->cub->file_without_split[i + 1] == '\n')
			return (true);
	}
	return (false);
}
