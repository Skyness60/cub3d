/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:00:51 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 16:56:04 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static char	*create_color_string(t_data *data, char **rgb)
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

void	check_color(t_data *data, char **tab, int i, bool check)
{
	char	**rgb;
	int		k;
	int		j;
	char	*color_str;

	k = -1;
	rgb = ft_split(tab[i], ",FC \t\n\v\f");
	if (!rgb)
		return (clear_all(data), ft_dprintf(2, "Error\nMalloc error\n"), exit(1));
	add_ptr_tab(data->trash_ptr, (void **)rgb, ft_tablen(rgb), true);
	while (rgb[++k])
	{
		j = -1;
		if (!ft_isdigit(rgb[k][++j]) || ft_tablen(rgb) != 3)
			return (clear_all(data), ft_dprintf(2, "Error\nInvalid color\n"), \
			exit(1));
	}
	color_str = create_color_string(data, rgb);
	if (check == true)
		data->cub->char_floor = color_str;
	else
		data->cub->char_ceiling = color_str;
	add_ptr(data->trash_ptr, color_str);
}
