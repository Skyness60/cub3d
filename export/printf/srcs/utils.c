/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 07:59:08 by sperron           #+#    #+#             */
/*   Updated: 2024/11/18 15:30:23 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_puthexa(char form, unsigned int nbr, int fd)
{
	int		count;
	char	*hexa;

	hexa = NULL;
	if (form == 'x')
		hexa = "0123456789abcdef";
	else if (form == 'X')
		hexa = "0123456789ABCDEF";
	if (nbr < 16)
	{
		pf_char('0', fd);
		count = 1;
	}
	else
		count = 0;
	if (nbr >= 16)
		count += ft_puthexa(form, nbr / 16, fd);
	pf_char(hexa[nbr % 16], fd);
	return (count + 1);
}

int	pf_putnbr_unsigned(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += pf_putnbr_unsigned(n / 10, fd);
	}
	count += pf_char(n % 10 + 48, fd);
	return (count);
}

int	pf_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		count += pf_char('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		count += pf_putnbr(n / 10, fd);
	}
	count += pf_char(n % 10 + '0', fd);
	return (count);
}

int	pf_char(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	pf_str(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (write(fd, "(null)", 6));
	}
	while (str[i] != '\0')
	{
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}
