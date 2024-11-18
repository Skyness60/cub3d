/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:08:47 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 08:45:59 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_printadress(const unsigned long n, int fd)
{
	if (n / 16)
		return (ft_printadress(n / 16, fd) + ft_printadress(n % 16, fd));
	else if (!(n / 10))
		pf_char(n + '0', fd);
	else
		pf_char((char) n - 10 + 'a', fd);
	return (1);
}

static int	ft_putpointer(void *adress, int fd)
{
	if (!adress)
		return (pf_str("(nil)", fd));
	pf_str("0x", fd);
	return (2 + ft_printadress((unsigned long) adress, fd));
}

static int	conv(char form, va_list args, int fd)
{
	if (form == 'c')
		return (pf_char((char) va_arg(args, int), fd));
	else if (form == 's')
		return (pf_str(va_arg(args, char *), fd));
	else if (form == 'p')
		return (ft_putpointer(va_arg(args, void *), fd));
	else if (form == 'd' || form == 'i')
		return (pf_putnbr(va_arg(args, int), fd));
	else if (form == 'u')
		return (pf_putnbr_unsigned(va_arg(args, unsigned int), fd));
	else if (form == 'x' || form == 'X')
		return (ft_puthexa(form, va_arg(args, unsigned int), fd));
	else if (form == '%')
		return (pf_char('%', fd));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		nb;

	va_start(args, format);
	i = 0;
	nb = 0;
	if (!format)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			nb += conv(format[i++ + 1], args, 1);
		else
			nb += pf_char(format[i], 1);
		i++;
	}
	return (va_end(args), nb);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		nb;

	va_start(args, format);
	i = 0;
	nb = 0;
	if (!format)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			nb += conv(format[i++ + 1], args, fd);
		else
			nb += pf_char(format[i], fd);
		i++;
	}
	return (va_end(args), nb);
}
