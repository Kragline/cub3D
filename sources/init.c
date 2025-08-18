/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:56:47 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 17:28:12 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_cub3D	*init_cub(void)
{
	t_cub3D	*cub;

	cub = malloc(sizeof(t_cub3D));
	if (!cub)
		return (NULL);
	cub->colors = malloc(sizeof(t_colors));
	if (!cub->colors)
		return (free(cub), NULL);
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		return (free(cub->colors), free(cub), NULL);
	cub->textures = malloc(sizeof(t_textures));
	if (!cub->textures)
		return (free(cub->map), free(cub->colors), free(cub), NULL);
	cub->map->grid = NULL;
	cub->textures->east = NULL;
	cub->textures->west = NULL;
	cub->textures->north = NULL;
	cub->textures->south = NULL;
	cub->mlx = NULL;
	cub->mlx_win = NULL;
	return (cub);
}
