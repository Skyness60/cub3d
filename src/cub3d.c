/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:35:41 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 11:01:06 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main_cub3d(char *av)
{
	t_data	*data;

	(void)av;
	init_data(&data);
	debug_gc(data->trash_ptr);
	return (clear_all(data), 0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_dprintf(2, "Error\nWrong number of arguments\n"), 1);
	return (main_cub3d(av[1]));
}
