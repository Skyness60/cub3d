/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:39:22 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 10:26:37 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

void	clear_fds(t_garb_d *trash_fds)
{
	size_t	i;

	i = -1;
	while (++i < trash_fds->count)
		if (trash_fds->fds[i] != -1)
			close(trash_fds->fds[i]);
	free(trash_fds->fds);
	trash_fds->fds = NULL;
	trash_fds->count = 0;
	trash_fds->capacite = 2;
}
