/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:43:08 by sperron           #+#    #+#             */
/*   Updated: 2024/12/18 16:28:20 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_all(t_data *data)
{
	free_all(data->trash_ptr);
	free(data->trash_ptr);
	clear_fds(data->trash_fds);
	free(data->trash_fds);
	free(data);
}
