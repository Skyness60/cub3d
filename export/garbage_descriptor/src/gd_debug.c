/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:44:29 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 10:26:41 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

void	debug_gd(t_garb_d *trash_fds)
{
	size_t	i;

	i = -1;
	if (trash_fds == NULL)
		return (gd_error(trash_fds, GD_EMPTY_TRASH_ERROR));
	printf("=== Garbage Descriptor Stats ===\n");
	printf("Nombre de descripteur : %zu\n", trash_fds->count);
	printf("Capacité : %zu\n", trash_fds->capacite);
	while (++i < trash_fds->count)
		printf("Descripteur %zu: %p\n", i, trash_fds->fds[i]);
	printf("================================\n");
}
