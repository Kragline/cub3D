/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:59:10 by armarake          #+#    #+#             */
/*   Updated: 2025/08/29 16:02:30 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_spawn(int c)
{
	return (c == ('N' - '0') || c == ('S' - '0')
		|| c == ('E' - '0') || c == ('W' - '0'));
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

static bool	dfs_outside(int **grid, int x, int y, t_cub3d *cub)
{
	if (x < 0 || y < 0 || x >= cub->map->rows || y >= cub->map->cols)
		return (true);
	if (grid[x][y] == -2)
		return (true);
	if (grid[x][y] == 1)
		return (true);
	if (grid[x][y] == 0 || is_spawn(grid[x][y]))
		return (false);
	if (grid[x][y] != -1)
		return (true);
	grid[x][y] = -2;
	return (dfs_outside(grid, x - 1, y, cub)
		&& dfs_outside(grid, x + 1, y, cub)
		&& dfs_outside(grid, x, y - 1, cub)
		&& dfs_outside(grid, x, y + 1, cub));
}

bool	map_is_closed(t_cub3d *cub)
{
	int		i;
	int		**grid;
	bool	is_closed;

	i = -1;
	is_closed = true;
	grid = dup_grid(cub->map->rows, cub->map->cols, cub->map->grid);
	if (!grid)
		parsing_error(cub, NULL, NULL, "Failed to allocate map for dfs");
	while (++i < cub->map->cols)
		if (!dfs_outside(grid, 0, i, cub)
			|| !dfs_outside(grid, cub->map->rows - 1, i, cub))
			return (free_grid(&grid), false);
	i = -1;
	while (++i < cub->map->rows)
		if (!dfs_outside(grid, i, 0, cub)
			|| !dfs_outside(grid, i, cub->map->cols - 1, cub))
			return (free_grid(&grid), false);
	return (free_grid(&grid), true);
}
