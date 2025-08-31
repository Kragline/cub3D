/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:46:47 by armarake          #+#    #+#             */
/*   Updated: 2025/08/31 17:36:05 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_spawn(char c)
{
	if (c == ('N' - '0') || c == ('S' - '0')
		|| c == ('E' - '0') || c == ('W' - '0'))
		return (true);
	return (false);
}

bool	line_is_empty(char *line)
{
	int	i;

	if (!line)
		return (true);
	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_line(char *line)
{
	int		i;

	if (!line)
		return (false);
	if (line_is_empty(line))
		return (false);
	i = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	is_all_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	file_is_empty(char *filname)
{
	int		fd;
	char	buf;
	ssize_t	bytes_read;

	fd = open(filname, O_RDONLY);
	if (fd == -1)
		return (print_error("Can't open the map"), true);
	bytes_read = read(fd, &buf, 1);
	if (!bytes_read)
		return (print_error("File is empty"), close(fd), true);
	return (close(fd), false);
}
