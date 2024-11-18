/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:12:40 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 15:30:42 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include "../../libft/libft.h"

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_puthexa(char form, unsigned int nbr, int fd);
int		pf_putnbr_unsigned(unsigned int n, int fd);
int		pf_char(int c, int fd);
int		pf_str(char *str, int fd);
int		pf_putnbr(int n, int fd);
#endif