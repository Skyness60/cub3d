/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:34:37 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/25 14:24:48 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_visited(t_raycasting *raycasting, char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
		;
	raycasting->visited = malloc(sizeof(bool *) * i + 1);
	i = -1;
	while (++i && map[i])
	{
		while (map[i][++j])
			raycasting->visited[i][j] = 0;
		raycasting->visited[i][j] = NULL;
		j = -1;
	}
}

static void	redimension_bis()
{
	
}

static void	redimension_and_display(t_texture img, double size, 
									t_raycasting *raycasting)
{
	void	*new_img;
	double	new_height;
	double	new_width;
	double	x_ratio;
	double	y_ratio;
	
	new_height = size * img.height;
	new_width = size * img.width;
	x_ratio = img.width / new_width;
	y_ratio = img.height / new_height;
	new_img = mlx_new_image(raycasting->data->mlx->mlx, (int)new_width, \
	(int)new_height);
	redimension_bis()
}

void	display_texture(t_raycasting *raycasting, bool x, double taille)
{
	if (x)
	{
		if (raycasting->angle < PI / 4 || raycasting->angle > PI + PI * 3 / 4)
			redimension_and_display(raycasting->data->cub->texture[EAST], \
			taille, raycasting);
		else
			redimension_and_display(raycasting->data->cub->texture[WEST], \
			taille, raycasting);
	}
	else
	{
		if (raycasting->angle < PI * 3 / 4 && raycasting->angle > PI / 4)
			redimension_and_display(raycasting->data->cub->texture[NORTH], \
			taille, raycasting);
		else
			redimension_and_display(raycasting->data->cub->texture[SOUTH], \
			taille, raycasting);
		
	}
}
