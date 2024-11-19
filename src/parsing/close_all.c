/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:41:54 by sperron           #+#    #+#             */
/*   Updated: 2024/11/19 13:43:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	close_all(t_data *data, char *stingError)
{
	clear_all(data);
	ft_dprintf(2, "Error\n%s\n", stingError);
	exit(1);
}
