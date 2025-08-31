/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:10:55 by armarake          #+#    #+#             */
/*   Updated: 2025/08/31 18:09:16 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	missing_values(t_cub3d *cub)
{
	if (!cub->map->grid)
		return (print_error("No map allocated"), true);
	if (cub->map->grid
		&& cub->colors->ceiling == INT_MIN && cub->colors->floor == INT_MIN
		&& !cub->textures->ea_name && !cub->textures->we_name
		&& !cub->textures->no_name && !cub->textures->so_name)
		return (print_error("Map before textures"), true);
	if (cub->colors->ceiling == INT_MIN)
		return (print_error("No ceiling color"), true);
	if (cub->colors->floor == INT_MIN)
		return (print_error("No floor color"), true);
	if (!cub->textures->ea_name)
		return (print_error("No east texture"), true);
	if (!cub->textures->we_name)
		return (print_error("No west texture"), true);
	if (!cub->textures->no_name)
		return (print_error("No north texture"), true);
	if (!cub->textures->so_name)
		return (print_error("No south texture"), true);
	return (false);
}

void	find_start_pos(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map->rows)
	{
		j = 0;
		while (j < cub->map->cols)
		{
			if (is_spawn(cub->map->grid[i][j]))
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

void	validate_edges(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < cub->map->cols)
	{
		if (cub->map->grid[0][i] == 0 || is_spawn(cub->map->grid[0][i]))
			parsing_error(cub, NULL, NULL, TOP_MESSAGE);
		if (cub->map->grid[cub->map->rows - 1][i] == 0
			|| is_spawn(cub->map->grid[cub->map->rows - 1][i]))
			parsing_error(cub, NULL, NULL, BOTTOM_MESSAGE);
	}
	i = -1;
	while (++i < cub->map->rows)
	{
		if (cub->map->grid[i][0] == 0 || is_spawn(cub->map->grid[i][0]))
			parsing_error(cub, NULL, NULL, LEFT_MESSAGE);
		if (cub->map->grid[i][cub->map->cols - 1] == 0
			|| is_spawn(cub->map->grid[i][cub->map->cols - 1]))
			parsing_error(cub, NULL, NULL, RIGHT_MESSAGE);
	}
}

bool	ends_with_cub(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int	safe_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
