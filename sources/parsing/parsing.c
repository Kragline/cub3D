/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:56:45 by armarake          #+#    #+#             */
/*   Updated: 2025/08/24 13:52:16 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	change_the_line(bool change_line, char **line, t_cub3d *cub)
{
	if (change_line)
	{
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = get_next_line(cub->map->map_fd);
		cub->map->lines_read++;
		if (!*line)
			parsing_error(cub, NULL, line, "Invalid file");
	}
}

static bool	st_elems(char **line, bool *change_line,
				t_state *state, t_cub3d *cub)
{
	if (line_is_empty(*line))
		return (true);
	if (try_parse_element(line, cub))
		return (true);
	if (is_map_line(*line))
	{
		*state = ST_MAP;
		*change_line = false;
		return (true);
	}
	return (false);
}

static void	st_map(char **line, bool *change_line, t_state *state, t_cub3d *cub)
{
	allocate_map(cub, line);
	*change_line = true;
	*state = ST_DONE;
}

static void	read_map(t_cub3d *cub)
{
	bool	change_line;
	char	*line;
	t_state	state;

	state = ST_ELEMS;
	line = NULL;
	change_line = true;
	while (state != ST_DONE)
	{
		change_the_line(change_line, &line, cub);
		if (state == ST_ELEMS)
		{
			if (st_elems(&line, &change_line, &state, cub))
				continue ;
			parsing_error(cub, NULL, &line, "Unknown line before map");
		}
		else if (state == ST_MAP)
			st_map(&line, &change_line, &state, cub);
		else
		{
			if (!line_is_empty(line))
				parsing_error(cub, NULL, &line, "Non-empty content after map");
		}
	}
	get_next_line(-1);
}

bool	parse_the_map(char *filename, t_cub3d *cub)
{
	if (!ends_with_cub(filename))
		return (print_error("Map name must end with .cub"), false);
	cub->map->map_fd = open(filename, O_RDONLY);
	cub->map->filename = filename;
	if (cub->map->map_fd == -1)
		return (print_error("Can't open the map"), false);
	if (file_is_empty(filename))
		return (false);
	read_map(cub);
	if (missing_values(cub))
		return (false);
	if (!map_is_closed(cub))
		return (print_error("Map is not closed"), false);
	return (true);
}
