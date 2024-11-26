/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:34:37 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/26 13:38:07 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

typedef struct	s_redim
{
	double	new_height;
	double	new_width;
	double	x_ratio;
	double	y_ratio;
	void	*new_img;
	int		bpp_orig;
	int		new_bpp;
	int		sizeline_orig;
	int		new_sizeline;
	int		src_x;
	int		src_y;
	int		useless;	
}	t_redim;

void	init_visited(t_raycasting *raycasting, char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
		;
	raycasting->visited = malloc(sizeof(bool *) * i);
	if (!raycasting->visited)
		close_all(raycasting->data, "Error w/ malloc");
	add_ptr(raycasting->data->raycast_trash, (void *)raycasting->visited);
	i = -1;
	while (map[++i])
	{
		while (map[i][++j])
			;
		raycasting->visited[i] = malloc(sizeof(bool) * j);
		j= -1;
		while (map[i][++j])
		{
			raycasting->visited[i][j] = 0;
			add_ptr(raycasting->data->raycast_trash, \
				(void *)raycasting->visited[i][j]);
		}
		j = -1;
	}
}

static void	redimension_bis(t_redim *redim, t_texture *img,
								t_raycasting *raycasting)
{
	int	*pixels;
	int	*new_pixels;
	int	x;
	int	y;

	x = -1;
	y = -1;
	pixels = (int *)mlx_get_data_addr(img->img, &redim->bpp_orig, \
	&redim->sizeline_orig, &redim->useless);
	new_pixels = (int *)mlx_get_data_addr(redim->new_img, &redim->new_bpp, 
	&redim->new_sizeline, &redim->useless);
	if (redim->new_bpp != 32 || redim->bpp_orig != 32)
		close_all(raycasting->data, "Cub3d only deals w/ 32 bits per pixel images");
	while (++x < redim->new_height)
	{
		while (++y < redim->new_width)
		{
			redim->src_x = (int)x * redim->x_ratio;
			redim->src_y = (int)y * redim->y_ratio;
			new_pixels[y * ((int)redim->new_sizeline / 4) + x] = \
			pixels[(int)redim->src_y * ((int)redim->sizeline_orig / 4) + x];
		}
	}
	mlx_put_image_to_window(raycasting->data->mlx->mlx, raycasting->data->mlx->win, \
	redim->new_img, WIN_HEIGHT / 2 - (int)redim->new_height / 2, raycasting->count_ray);
}

static void	redimension_and_display(t_texture *img, double size, 
									t_raycasting *raycasting)
{
	t_redim redim;
	
	redim.new_bpp = 0;
	redim.bpp_orig = 0;
	redim.new_sizeline = 0;
	redim.sizeline_orig = 0;
	redim.new_height = size * img->height;
	redim.new_width = size * img->width;
	redim.x_ratio = img->width / redim.new_width;
	redim.y_ratio = img->height / redim.new_height;
	redim.new_img = mlx_new_image(raycasting->data->mlx->mlx, \
	(int)redim.new_width, (int)redim.new_height);
	if (!redim.new_img)
		close_all(raycasting->data, "Mlx Error");
	add_ptr(raycasting->data->raycast_trash, redim.new_img);
	redimension_bis(&redim, img, raycasting);
}

void	display_texture(t_raycasting *raycasting, bool x, double taille)
{
	if (x)
	{
		if (raycasting->angle < PI / 4 || raycasting->angle > PI + PI * 3 / 4)
			redimension_and_display(&raycasting->data->cub->texture[EAST], \
			taille, raycasting);
		else
			redimension_and_display(&raycasting->data->cub->texture[WEST], \
			taille, raycasting);
	}
	else
	{
		if (raycasting->angle < PI * 3 / 4 && raycasting->angle > PI / 4)
			redimension_and_display(&raycasting->data->cub->texture[NORTH], \
			taille, raycasting);
		else
			redimension_and_display(&raycasting->data->cub->texture[SOUTH], \
			taille, raycasting);
		
	}
}
