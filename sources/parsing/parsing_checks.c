/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:46:47 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 16:09:02 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		if (!is_map_char(line[i]) && !is_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}

// bool	map_is_closed(t_cub3d *cub)
// {
// 	int	i;
// 	int	len;

// 	if (!is_all_wall(cub->map->grid[0])
// 		|| !is_all_wall(cub->map->grid[cub->map->rows - 1]))
// 		return (false);
// 	i = 0;
// 	while (cub->map->grid[i])
// 	{
// 		len = ft_strlen(cub->map->grid[i]);
// 		if (cub->map->grid[i][0] != '1' || cub->map->grid[i][len - 1] != '1')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

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
