/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:30:35 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 08:43:23 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	remove_ptr(t_garb_c *trash, void *ptr)
{
	size_t	i;
	void	**new_ptr;

	i = -1;
	new_ptr = NULL;
	if (trash == NULL || ptr == NULL)
		return ;
	while (++i < trash->count)
	{
		if (trash->ptr_arr[i] == ptr)
		{
			free(trash->ptr_arr[i]);
			trash->ptr_arr[i] = trash->ptr_arr[--trash->count];
			if (trash->count < trash->capacite / 2 && trash->capacite > 2)
			{
				trash->capacite /= 2;
				new_ptr = ft_realloc(trash->ptr_arr, trash->capacite * 2 \
				* sizeof(void *), trash->capacite * sizeof(void *));
				if (!new_ptr)
					return (gc_error(GC_REALLOC_ERROR, trash));
				trash->ptr_arr = new_ptr;
			}
			return ;
		}
	}
}
