/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:59:10 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 20:38:59 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_walkable(int c)
{
	return (c == 0 || c == ('N' - '0') || c == ('S' - '0')
		|| c == ('E' - '0') || c == ('W' - '0'));
}

static bool	dfs(int **grid, int x, int y, t_cub3d *cub)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (x < 0 || y < 0 || x >= cub->map->rows || y >= cub->map->cols)
		return (false);
	if (grid[x][y] == -1 || grid[x][y] == 1)
		return (true);
	if (!is_walkable(grid[x][y]))
		return (true);
	grid[x][y] = 'V';
	up = dfs(grid, x - 1, y, cub);
	down = dfs(grid, x + 1, y, cub);
	left = dfs(grid, x, y - 1, cub);
	right = dfs(grid, x, y + 1, cub);
	return (up && down && left && right);
}

static int	**dup_grid(int rows, int cols, int **grid)
{
	int	i;
	int	j;
	int	**copy;

	i = 0;
	copy = malloc(sizeof(int *) * (rows + 1));
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
	return (copy);
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
			if (cub->map->grid[i][j] == ('N' - '0')
			|| cub->map->grid[i][j] == ('S' - '0')
			|| cub->map->grid[i][j] == ('E' - '0')
			|| cub->map->grid[i][j] == ('W' - '0'))
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

bool	map_is_closed(t_cub3d *cub)
{
	int		**grid;
	bool	is_closed;

	grid = dup_grid(cub->map->rows, cub->map->cols, cub->map->grid);
	find_start_pos(cub);
	if (cub->map->player_x == INT_MIN || cub->map->player_y == INT_MIN)
	{
		free_grid(&grid);
		parsing_error(cub, NULL, NULL, "No player position in the map");
	}
	is_closed = dfs(grid, cub->map->player_x, cub->map->player_y, cub);
	free_grid(&grid);
	return (is_closed);
}
