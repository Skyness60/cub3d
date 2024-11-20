/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:35:41 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 16:17:24 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_cub3d(char *av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_dprintf(2, "Error\nMalloc error for t_data\n"), 1);
	init_data(data);
	set_cub(data, av);
	if (data->cub->map->height < 3 || data->cub->map->width < 3)
		return (close_all(data, "Map error"), 1);
	open_cub3d(data);
	return (clear_all(data), 0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_dprintf(2, "Error\nWrong number of arguments\n"), 1);
	if (check_name(av[1]))
		return (ft_dprintf(2, "Error\nWrong file extension\n"), 1);
	return (main_cub3d(av[1]));
}
