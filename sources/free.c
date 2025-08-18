/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:11:23 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 19:34:05 by armarake         ###   ########.fr       */
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
	// destroy mlx window and connection
	if (cub->textures->east_name)
		free(cub->textures->east_name);
	if (cub->textures->west_name)
		free(cub->textures->west_name);
	if (cub->textures->north_name)
		free(cub->textures->north_name);
	if (cub->textures->south_name)
		free(cub->textures->south_name);
	free(cub->colors);
	free(cub->map);
	free(cub->textures);
	free(cub);
}