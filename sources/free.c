/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:11:23 by armarake          #+#    #+#             */
/*   Updated: 2025/08/22 15:42:56 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_grid(char ***grid)
{
	int	i;

	i = 0;
	while ((*grid)[i])
	{
		free((*grid)[i]);
		i++;
	}
	free((*grid));
}

void	free_cub(t_cub3D *cub)
{
	if (!cub)
		return ;
	if (cub->map->grid)
		free_grid(&cub->map->grid);
	// free mlx textures
	if (cub->textures->ea_name)
		free(cub->textures->ea_name);
	if (cub->textures->we_name)
		free(cub->textures->we_name);
	if (cub->textures->no_name)
		free(cub->textures->no_name);
	if (cub->textures->so_name)
		free(cub->textures->so_name);
	if (cub->map->map_fd != -1)
		close(cub->map->map_fd);
	if (cub->colors)
		free(cub->colors);
	if (cub->map)
		free(cub->map);
	if (cub->textures)
		free(cub->textures);
	if (cub->mlx_win)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
}
