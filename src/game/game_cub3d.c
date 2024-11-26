/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:09 by sperron           #+#    #+#             */
/*   Updated: 2024/11/26 14:13:49 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d(t_data *data)
{
	raycast(data);
	handle_close(data);
	handle_move(data);
	mlx_loop(data->mlx->mlx);
	free_all(data->raycast_trash);
	return (0);
}