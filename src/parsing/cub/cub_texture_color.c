/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:00:51 by sperron           #+#    #+#             */
/*   Updated: 2025/01/02 16:42:26 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_hexa_to_str_utils(char *result, int len, unsigned int nbr)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	while (len > 0)
	{
		result[--len] = hexa[nbr % 16];
		nbr /= 16;
	}
	return (result);
}

char	*ft_hexa_to_str(t_data *data, unsigned int nbr)
{
	int				len;
	unsigned int	temp;
	char			*result;

	if (nbr == 0)
	{
		len = 1;
		temp = 0;
	}
	else
	{
		len = 0;
		temp = nbr;
		while (temp > 0)
		{
			temp /= 16;
			len++;
		}
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (clear_all(data), ft_dprintf(2, "Error\nMalloc error\n"), \
		exit(1), NULL);
	return (result = ft_hexa_to_str_utils(result, len, nbr), \
	result[len] = '\0', add_ptr(data->trash_ptr, result), result);
}

static char	*cs(t_data *data, char **rgb)
{
	char	*color_str;
	char	*hex_value;
	int		j;
	char	padded_hex[3];

	color_str = malloc(7);
	if (!color_str)
		return (clear_all(data), ft_dprintf(2, "Error\nMalloc error\n"), \
		exit(1), NULL);
	color_str[0] = '\0';
	j = -1;
	while (++j < 3)
	{
		hex_value = ft_hexa_to_str(data, ft_atoi(rgb[j]));
		if (ft_strlen(hex_value) == 1)
		{
			padded_hex[0] = '0';
			padded_hex[1] = hex_value[0];
			padded_hex[2] = '\0';
			ft_strcat(color_str, padded_hex);
		}
		else
			ft_strcat(color_str, hex_value);
	}
	return (color_str);
}

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
	|| (ft_tablen(rgb) != 2 && count_char(rgb[0], ',') + count_char(rgb[1], ',') != 3)))
		return (close_all(data, "Color format error"), false);
	i = -1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (close_all(data, "Color value error"), false);
	return (true);
}

void	check_color(t_data *data, char **tab, int i, bool check)
{
	char	**rgb;

	if ((check && data->cub->char_floor[0] != '\0') \
	|| (!check && data->cub->char_ceiling[0] != '\0'))
		return (close_all(data, "Duplicate color"));
	rgb = ft_split(tab[i], "FC \t\n\v\f");
	if (!rgb)
		return (close_all(data, "Malloc error"));
	add_ptr_tab(data->trash_ptr, (void **)rgb, ft_tablen(rgb), true);
	format_rgb(rgb, data);
	if (check == true)
		return (data->cub->char_floor = cs(data, rgb), \
		add_ptr(data->trash_ptr, data->cub->char_floor));
	return (data->cub->char_ceiling = cs(data, rgb), \
	add_ptr(data->trash_ptr, data->cub->char_ceiling));
}
