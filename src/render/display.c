/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:59 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/14 19:04:39 by sperron          ###   ########.fr       */
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
	int	k;
	int	tex_x;
	int	tex_y;

	i = 0;
	(void)ratio;
	k = WIN_HEIGHT / 2 - size_img / 2;
	if (size_img > WIN_HEIGHT)
		size_img = WIN_HEIGHT;
	while (i < size_img)
	{
		tex_x = (int)(texture.width * raycast->precise_hit);
		if (tex_x >= texture.width) // Secure the index
			tex_x = texture.width - 1;
		tex_y = (i * texture.height) / size_img; // Calculate the corresponding y coordinate in the texture
		if (tex_y >= texture.height) // Ensure tex_y is within bounds
			tex_y = texture.height - 1;
		
		// Filling the column in the new buffer
		if (k >= 0 && k < WIN_HEIGHT) // Ensure k is within bounds
		{
			raycast->new_buff[k * WIN_WIDTH + raycast->count_r] = texture.buffer[tex_y * texture.width + tex_x];
		}
		k++; // Move down the column
		i++; // Move to the next pixel in the column
	}
}

static void	fill_column(t_raycast *raycast, t_texture texture)
{
	double	len;
	int		col_size;
	int		ratio;

	// Calculate the length
	len = (raycast->x == 1) ? raycast->len_x : raycast->len_y;
	if (len < 0.25) // Minimum limit to avoid oversized columns
		len = 0.25;

	// Calculate column size and ratio
	col_size = WIN_HEIGHT / len;
	if (col_size > WIN_HEIGHT)
		col_size = WIN_HEIGHT;
	ratio = (col_size + texture.height - 1) / texture.height;
	if (ratio < 1)
		ratio = 1;

	// Fill the column
	fill_column_bis(raycast, texture, col_size, ratio);

	// Fill ceiling/floor if the column is smaller than the window
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
