/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:54:28 by sperron           #+#    #+#             */
/*   Updated: 2024/05/28 14:52:24 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = gnl_strlen(s1) + gnl_strlen(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[sizetotal] = 0;
	return (res);
}

char	*gnl_strchr(const char *string, int searchedChar)
{
	char	*str;

	str = (char *)string;
	while (*str != searchedChar && *str != 0)
		str++;
	if (*str == searchedChar)
		return (str);
	else
		return (NULL);
}

void	gnl_bzero(void *s, unsigned int n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = '\0';
}

void	*gnl_calloc(unsigned int count, unsigned int size)
{
	void	*pointer;

	pointer = malloc(count * size);
	if (!pointer)
		return (NULL);
	gnl_bzero(pointer, size * count);
	return (pointer);
}

size_t	gnl_strlen(const char *theString)
{
	int	i;

	i = 0;
	if (!theString)
		return (0);
	while (theString[i])
		i++;
	return (i);
}