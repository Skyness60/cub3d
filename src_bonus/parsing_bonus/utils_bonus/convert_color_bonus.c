/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:12:47 by sperron           #+#    #+#             */
/*   Updated: 2024/12/14 14:29:33 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	char_to_hex(char *str, t_data *data)
{
	int	i;
	int	hex;

	i = -1;
	hex = 0;
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			hex = hex * 16 + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			hex = hex * 16 + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			hex = hex * 16 + str[i] - 'a' + 10;
		else
			return (close_all(data, "Wrong color format"), 1);
	}
	return (hex);
}

void	convert_color(t_data *data)
{
	data->cub->hex_floor = char_to_hex(data->cub->char_floor, data);
	data->cub->hex_ceiling = char_to_hex(data->cub->char_ceiling, data);
}
