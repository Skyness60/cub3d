/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture_color_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:42:35 by sperron           #+#    #+#             */
/*   Updated: 2025/01/03 10:43:44 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}

bool	format_rgb(char **rgb, t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < 3)
		if (rgb[i] && rgb[i][ft_strlen(rgb[i]) - 1] == ',')
			count++;
	if (count != 2 && ((ft_tablen(rgb) != 1 && count_char(rgb[0], ',') != 3) \
	|| (ft_tablen(rgb) != 2 \
	&& count_char(rgb[0], ',') + count_char(rgb[1], ',') != 3)))
		return (close_all(data, "Color format error"), false);
	i = -1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (close_all(data, "Color value error"), false);
	return (true);
}
