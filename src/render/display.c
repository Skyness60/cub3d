/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:59 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/14 18:21:50 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ceiling_and_floor(t_raycast *raycast, int size_img)
{
	int	i;

	// Fill the ceiling
	i = WIN_HEIGHT / 2 - size_img / 2;
	while (i >= 0 && i < WIN_HEIGHT / 2)
		raycast->new_buff[i-- * WIN_WIDTH + raycast->count_r] = raycast->data->cub->hex_ceiling;

	// Fill the floor
	i = WIN_HEIGHT / 2 + size_img / 2;
	while (i >= WIN_HEIGHT / 2 && i < WIN_HEIGHT)
		raycast->new_buff[i++ * WIN_WIDTH + raycast->count_r] = raycast->data->cub->hex_floor;
}

static void	fill_column_bis(t_raycast *raycast, t_texture texture, int size_img, int ratio)
{
	int	i;
	int	j;
	int	k;
	int	tex_x;

	i = 0;
	k = WIN_HEIGHT / 2 - size_img / 2;
	while (i < texture.height)
	{
		j = 0;
		tex_x = (int)(texture.width * raycast->precise_hit);
		if (tex_x >= texture.width) // Sécuriser l'indice
			tex_x = texture.width - 1;
		while (j < ratio && k < WIN_HEIGHT)
		{
			raycast->new_buff[k++ * WIN_WIDTH + raycast->count_r] = \
			texture.buffer[i * texture.width + tex_x];
			j++;
		}
		i++;
	}
}


static void	fill_column(t_raycast *raycast, t_texture texture)
{
	double	len;
	int		col_size;
	int		ratio;

	// Calcul de la longueur
	len = (raycast->x == 1) ? raycast->len_x : raycast->len_y;
	if (len < 0.25) // Limite minimale pour éviter des colonnes démesurées
		len = 0.25;

	// Taille et ratio des colonnes
	col_size = WIN_HEIGHT / len;
	if (col_size > WIN_HEIGHT)
		col_size = WIN_HEIGHT;
	ratio = (col_size + texture.height - 1) / texture.height;
	if (ratio < 1)
		ratio = 1;

	// Remplissage de la colonne
	fill_column_bis(raycast, texture, col_size, ratio);

	// Remplissage plafond/sol si la colonne est plus petite que la fenêtre
	if (col_size < WIN_HEIGHT)
		ceiling_and_floor(raycast, col_size);
}


void	construct_img(t_data *data, t_raycast *raycast)
{
	// Determine which texture to use based on the ray direction and angle
	if (raycast->x == 1 && raycast->angle > PI / 2 && raycast->angle < PI + PI / 2)
		fill_column(raycast, data->cub->texture[WEST]);
	else if (raycast->x == 1)
		fill_column(raycast, data->cub->texture[EAST]);
	else if (raycast->angle < PI)
		fill_column(raycast, data->cub->texture[NORTH]);
	else
		fill_column(raycast, data->cub->texture[SOUTH]);
}
