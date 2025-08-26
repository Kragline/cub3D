/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:56:45 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 17:31:06 by armarake         ###   ########.fr       */
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

static bool	is_walkable(int c)
{
    return (c == 0 || c == ('N' - '0') || c == ('S' - '0') || c == ('E' - '0') || c == ('W' - '0'));
}

static bool	dfs(int **grid, int x, int y, int rows, int cols)
{
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return (false);
    if (grid[x][y] == -1 || grid[x][y] == 1)
        return (true);
    if (!is_walkable(grid[x][y]))
        return (true);
    grid[x][y] = 'V';
    bool up    = dfs(grid, x - 1, y, rows, cols);
    bool down  = dfs(grid, x + 1, y, rows, cols);
    bool left  = dfs(grid, x, y - 1, rows, cols);
    bool right = dfs(grid, x, y + 1, rows, cols);
    return (up && down && left && right);
}

int	**dup_grid(int rows, int cols, int **grid)
{
	int	i = 0;
	int	j;
    int **copy = malloc(sizeof(int *) * (rows + 1));
	while (i < rows)
	{
		j = 0;
		copy[i] = malloc(sizeof(int) * cols);
		while (j < cols)
		{
			copy[i][j] = grid[i][j];
			j++;
		}
		i++;
	}
    copy[rows] = NULL;
    return copy;
}

static void	find_start_pos(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map->rows)
	{
		j = 0;
		while (j < cub->map->cols)
		{
			if (cub->map->grid[i][j] == ('N' - '0') || cub->map->grid[i][j] == ('S' - '0') || cub->map->grid[i][j] == ('E' - '0') || cub->map->grid[i][j] == ('W' - '0'))
			{
				cub->map->player_x = i;
				cub->map->player_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

bool map_is_closed(t_cub3d *cub)
{
	int **grid = dup_grid(cub->map->rows, cub->map->cols, cub->map->grid);
	find_start_pos(cub);
	if (cub->map->player_x == INT_MIN || cub->map->player_y == INT_MIN)
	{
		free_grid(&grid);
		parsing_error(cub, NULL, NULL, "No player position inted map");
	}
	bool val = dfs(grid, cub->map->player_x, cub->map->player_y, cub->map->rows, cub->map->cols);
	free_grid(&grid);
    return (val);
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
