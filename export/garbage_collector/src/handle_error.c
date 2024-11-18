/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:33:24 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 08:43:33 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	gc_error(t_error error, t_garb_c *trash)
{
	if (error == GC_MALLOC_ERROR)
	{
		gc_putstr("Malloc error\n");
		free_all(trash);
	}
	else if (error == GC_REALLOC_ERROR)
	{
		gc_putstr("Realloc error\n");
		free_all(trash);
	}
}
