/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:20:08 by jlebard           #+#    #+#             */
/*   Updated: 2024/12/11 12:28:50 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	fill_buff(t_raycast *raycast, int color, int i, int count_r)
{
	(void)color;
	if (i < WIN_HEIGHT / 2)
	{
		while (i >= 0)
		{
			raycast->fin_buf[i + count_r] = 0;
			i--;
		}
	}
	else
	{
		while (i < WIN_HEIGHT)
		{
			raycast->fin_buf[i + count_r] = 0;
			i++;
		}	
	}
}

static void	get_final_img(t_raycast *raycast, t_texture texture, double len,
							int count_r)
{
	double	ratio;
	int		size_img;
	int		i;

	i = -1;	
	size_img = texture.height * PROJ_PLANE_DT / len;
	if (size_img > WIN_HEIGHT)
		size_img = WIN_HEIGHT;
	ratio = texture.height / size_img;
	if (count_r == 500)
	{
		printf("proj plane dt = %f\n", PROJ_PLANE_DT);
		printf("taille de l image de base = %d\n", texture.height);
		printf("distance perso mur = %f\n", len);
		printf("taille rayon mur pixels = %d\n", size_img);
		printf("ratio (proportion en pixels du rayon que l on affiche par rapport a la taille en pixels de l image de base) = %f\n", ratio);
		printf("float de l impact sur le mur = %f\n", raycast->precise_impact);
	}
	while (++i < size_img)
	{
		raycast->fin_buf[(WIN_WIDTH / 2 - size_img / 2 + i) + count_r] = \
		texture.buffer[(int)(i * ratio + raycast->precise_impact * \
		texture.height)];
	}
	i = WIN_HEIGHT / 2 - size_img / 2;
	fill_buff(raycast, raycast->data->cub->hex_floor, i, count_r);
	i = WIN_HEIGHT / 2 + size_img / 2;
	fill_buff(raycast, raycast->data->cub->hex_ceiling, i, count_r);
}

void	init_final_img(t_raycast *raycast)
{
	int	bpp;
	int	sizeline;
	int	endian;

	raycast->final_img = mlx_new_image(raycast->data->mlx->mlx, WIN_WIDTH, \
	WIN_HEIGHT);
	raycast->fin_buf = (int*)mlx_get_data_addr(raycast->final_img, &bpp, \
	&sizeline, &endian);
}

static void	define_precise_impact(t_raycast *raycast, bool x)
{
	if (x)
	{
		raycast->precise_impact = raycast->pos_x + \
		(raycast->len_x * cos(raycast->angle));
		raycast->precise_impact = (double)raycast->wall_y;
	}
	else
	{
		raycast->precise_impact = raycast->pos_y + \
		(raycast->len_y * sin(raycast->angle));
		raycast->precise_impact = (double)raycast->wall_x;
	}
}

void	display_walls(t_raycast *raycast, bool x, int count_r)
{
	t_texture	*imgs;
	
	imgs = raycast->data->cub->texture;
	define_precise_impact(raycast, x);
	if (x)
	{
		if (raycast->dir_x == 1)
			get_final_img(raycast, imgs[EAST], raycast->len_x, count_r);
		else
			get_final_img(raycast, imgs[WEST], raycast->len_x, count_r);
	}
	else
	{
		if (raycast->dir_y == 1)
			get_final_img(raycast, imgs[SOUTH], raycast->len_y, count_r);
		else
			get_final_img(raycast, imgs[NORTH], raycast->len_y, count_r);
	}
}
