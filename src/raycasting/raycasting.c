/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/20 08:30:14 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vec	*add_vecs(t_data *data, t_vec *u, t_vec *v)
{
	t_vec	*add_bis;

	add_bis = malloc(sizeof(t_vec));
	if (!add_bis)
		exit(EXIT_FAILURE);
	add_ptr(data->trash_ptr, add_bis);
	add_bis->x = u->x + v->x;
	add_bis->y = u->y + v->y;
	return (add_bis);
}

void	ray_loop(t_data *data, t_look *look, int cell_size)
{
	double	tan;
	int		i;

	i = 0;
	look->add = add_vecs(data, look->dir, look->pos);
	while(1)
	{
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
