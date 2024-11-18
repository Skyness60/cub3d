/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/18 16:56:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ray_loop(t_look *look, int cell_size)
{
	double	tan;
	int		i;

	i = 0;
	while (1)
	{
		tan = atan2(look->dirX, look->dirY);
		if (is_wall() == 1)
		{
			display_plane(i);
			break ;
		}
		else
			display_f_and_c(i);
		i += cell_size;
	}
}
