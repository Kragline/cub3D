/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:56:45 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 19:57:35 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static bool	line_is_empty(char *line)
// {
// 	int	i;
	
// 	if (line[0] == '\0' || line[0] == '\n')
// 		return (true);
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13) && line[i] != '\n')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// static bool	set_value(char *line, char **dest, t_cub3D *cub)
// {
// 	int	i;
	
// 	if (*dest)
// 	{
// 		print_error("Duplicate texture");
// 		free_cub(cub);
// 		exit(1);
// 	}
// 	i = 0;
// 	while (line[i] && line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13) && line[i] != '\n')
// 		i++;
// 	*dest = ft_substr(line, 0, i);
// 	return (true);
// }

// static bool	try_parse_element(char *line, t_cub3D *cub)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] && (line[i] == ' ' || line[i] >= 9 && line[i] <= 13))
// 	{
// 		if (line[i] == '\n')
// 			return (false);
// 		i++;
// 	}
// 	if (!ft_strncmp(line + i, "NO ", 3))
// 		return (set_value(line + i, &cub->textures->north_name, cub), true);
// 	else if (!ft_strncmp(line + i, "SO ", 3))
// 		return (set_value(line + i, &cub->textures->south_name, cub), true);
// 	else if (!ft_strncmp(line + i, "WE ", 3))
// 		return (set_value(line + i, &cub->textures->west_name, cub), true);
// 	else if (!ft_strncmp(line + i, "EA ", 3))
// 		return (set_value(line + i, &cub->textures->east_name, cub), true);
// 	else if (!ft_strncmp(line + i, "F ", 2))
// 		return (set_value(line + i, &cub->colors->floor, cub), true);
// 	else if (!ft_strncmp(line + i, "C ", 2))
// 		return (set_value(line + i, &cub->colors->ceiling, cub), true);
// 	return (false);
// }

// static void	read_map(int map_fd, t_cub3D *cub)
// {
// 	char	*line;
// 	t_state state;

// 	state = ST_ELEMS;
// 	while (state != ST_DONE)
// 	{
// 		if (line)
// 		{
// 			free(line);
// 			line = NULL;
// 		}
// 		line = get_next_line(map_fd);
// 		if (state == ST_ELEMS)
// 		{
// 			if (line_is_empty(line))
// 				continue;
// 			if (try_parse_element(line, cub))
// 				continue; // NO/SO/WE/EA/F/C
// 			if (looks_like_map_line(line))
// 			{
// 				state = ST_MAP;
// 				continue;
// 			}
// 			print_error("Unknown line before map");
// 		}
// 		else if (state == ST_MAP)
// 		{
// 			allocate_map(map_fd, cub, &line);
// 			state = ST_DONE;
// 		}
// 		else
// 		{
// 			// ST_DONE
// 			if (!line_is_empty(line))
// 				print_error("Non-empty content after map");
// 		}
// 	}
// }

bool	valiate(char *filname, t_cub3D *cub)
{
	int		map_fd;

	if (!ends_with_cub(filname))
		return (print_error("Map name must end with .cub"), false);
	map_fd = open(filname, O_RDONLY);
	if (map_fd == -1)
		return (print_error("Can't open the map"), false);
	(void)cub;// read_map(map_fd, cub);
	return (close(map_fd), true);
}