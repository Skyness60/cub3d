/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:32:34 by sperron           #+#    #+#             */
/*   Updated: 2024/11/20 15:29:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calculate_new_length(const char *line)
{
	int	i;
	int	new_length;

	i = 0;
	new_length = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
			new_length += 4;
		else
			new_length++;
		i++;
	}
	return (new_length);
}

static char	*create_new_line(const char *line, int new_length, t_data *data)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(new_length + 1);
	if (!new_line)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	add_ptr(data->trash_ptr, new_line);
	return (new_line);
}

static void	replace_tabs_with_spaces_for_line(char **map, int row, t_data *data)
{
	char	*line;
	int		new_length;
	char	*new_line;

	line = map[row];
	new_length = calculate_new_length(line);
	new_line = create_new_line(line, new_length, data);
	if (new_line)
		map[row] = new_line;
}

void	replace_tabs_with_spaces(char **map, t_data *data)
{
	int	row;

	row = -1;
	while (map[++row])
		replace_tabs_with_spaces_for_line(map, row, data);
}
