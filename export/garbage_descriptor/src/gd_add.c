/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:10:08 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 08:44:03 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

void	add_fd(t_garbage_descriptor *trash_fds, int fd)
{
	int	*tmp;

	tmp = NULL;
	if (fd == -1)
		return ;
	if (trash_fds->count == FD_MAX)
		return (gd_error(trash_fds, GD_FD_MAX_ERROR));
	if (trash_fds->count == trash_fds->capacite)
	{
		trash_fds->capacite *= 2;
		tmp = gd_realloc(trash_fds->fds, trash_fds->count * sizeof(int), \
		trash_fds->capacite * sizeof(int));
		if (tmp == NULL)
			return (gd_error(trash_fds, GD_REALLOC_ERROR));
		trash_fds->fds = tmp;
	}
	trash_fds->fds[trash_fds->count++] = fd;
}
