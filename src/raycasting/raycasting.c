/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:30:48 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/20 15:04:30 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	display_ray(t_data *data, t_player *player, double angle)
{
	double	delta_X;
	double	delta_Y;
	
	delta_X = CELL_SIZE / fabs(cos(angle));
	delta_Y = CELL_SIZE / fabs(sin(angle)); 
}

static void	send_rays(t_data *data)
{
	double	ray_angle;
	double	cam_angle;
	int		i;
	
	i = 0;
	cam_angle = data->player->angle;
	while (i < WIN_WIDTH)
	{
		ray_angle = cam_angle - (FOV / 2) + (i * FOV / WIN_WIDTH);
		display_ray(data, data->player, ray_angle);
		i++;
	}
}

static void	starting_pov(t_data *data)
{
	if (data->player->orientation == 'N')
		data->player->angle = PI / 2;
	else if (data->player->orientation == 'E')
		data->player->angle = 2 * PI;
	else if (data->player->orientation == 'W')
		data->player->angle = PI;
	else if (data->player->orientation == 'S')
		data->player->angle =  3 * PI / 2;		
}

void	raycasting(t_data *data)
{
	if (data->spawn == 1)
	{
		starting_pov(data);
		data->spawn = 0;
	}
	send_rays(data);
}
