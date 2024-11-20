/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 07:04:01 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 15:29:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_name(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 4)
		return (1);
	if (ft_strncmp(av + len - 4, ".cub", 4))
		return (1);
	return (0);
}

int	check_xpm(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 4)
		return (1);
	if (ft_strncmp(av + len - 4, ".xpm", 4))
		return (1);
	return (0);
}
