/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:20:08 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/27 14:50:51 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	redim_img(void *ptr, t_texture texture, int line_to_get, 
					int sizeline)
{
	int	ratio;
	
	ratio = sizeline / texture.height;
	 		
}

static void	*get_pixel_line(t_raycast *raycast, t_texture texture,
							double precise, double distance)
{
	int				line_to_get;
	void			*new_img;
	unsigned int	*buffer;
	int				bpp;
	int				size_line;
	int				useless;
	unsigned int	*new_buffer;

	raycast->size_displayed = PROJ_PLANE_DT * (WIN_HEIGHT / 2) / distance;
	line_to_get = (precise - floor(precise)) * texture.width;
	buffer = mlx_get_data_addr(texture.img, &bpp, &size_line, &useless);
	new_img = mlx_new_image(raycast->data->mlx->mlx, 1, \
	raycast->size_displayed);
	if (bpp != 32)
		close_all(raycast->data, "Cub3d only supports 32 bpp images");
	new_buffer = mlx_get_data_addr(new_img, &bpp, &size_line, &useless);
	redim_img(new_img, texture, line_to_get, );
	return (new_img);
}

static void	define_precise_impact(t_raycast *raycast, bool x)
{
	if (x)
	{
		raycast->impact_x = raycast->pos_x + \
		(raycast->len_x * cos(raycast->angle));
		raycast->impact_y = (double)raycast->wall_y;
	}
	else
	{
		raycast->impact_y = raycast->pos_y + \
		(raycast->len_y * sin(raycast->angle));
		raycast->impact_x = (double)raycast->wall_x;
	}
}

void	display_walls(t_raycast *raycast, bool x, int count_r)
{
	t_texture	*imgs;
	t_mlx		*mlx;
	void		*img;
	
	imgs = raycast->data->cub->texture;
	mlx = raycast->data->mlx;
	define_precise_impact(raycast, x);
	if (x)
	{
		if (raycast->dir_x == 1)
			img = get_pixel_line(raycast, imgs[EAST], raycast->impact_x, raycast->len_x);
		else
			img = get_pixel_line(raycast, imgs[WEST], raycast->impact_x, raycast->len_x);
	}
	else
	{
		if (raycast->dir_y == 1)
			img = get_pixel_line(raycast, imgs[SOUTH], raycast->impact_y, raycast->len_y);
		else
			img = get_pixel_line(raycast, imgs[NORTH], raycast->impact_y, raycast->len_y);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, count_r, raycast->low);
}
