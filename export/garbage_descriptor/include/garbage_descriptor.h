/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_descriptor.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:09:29 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 10:40:57 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_DESCRIPTOR_H
# define GARBAGE_DESCRIPTOR_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FD_MAX 1024

typedef enum e_error_gd
{
	GD_NO_ERROR,
	GD_REALLOC_ERROR,
	GD_FD_MAX_ERROR,
	GD_EMPTY_TRASH_ERROR,
	GD_MALLOC_ERROR
}			t_error_gd;

typedef struct s_garb_d
{
	int		*fds;
	size_t	capacite;
	size_t	count;
}				t_garb_d;

void	init_garbage_descriptor(t_garb_d *trash_fds);
void	*gd_realloc(void *fds, size_t old_size, size_t size);
void	add_fd(t_garb_d *trash_fds, int fd);
void	close_fd(t_garb_d *trash_fds, int fd);
void	clear_fds(t_garb_d *trash_fds);
void	debug_gd(t_garb_d *trash_fds);
void	gd_error(t_garb_d *trash_fds, t_error_gd error);

#endif