/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:35:01 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 10:26:39 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

void	close_fd(t_garb_d *trash_fds, int fd)
{
	size_t	i;

	i = -1;
	while (++i < trash_fds->count)
	{
		if (trash_fds->fds[i] == fd)
		{
			if (trash_fds->fds[i])
				close(trash_fds->fds[i]);
			trash_fds->fds[i] = -1;
		}
	}
}
