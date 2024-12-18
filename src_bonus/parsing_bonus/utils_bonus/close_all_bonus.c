/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:41:54 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 16:27:02 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_all(t_data *data, char *stingError)
{
	clear_all(data);
	ft_dprintf(2, "Error\n%s\n", stingError);
	exit(1);
}
