/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:13:14 by armarake          #+#    #+#             */
/*   Updated: 2025/08/24 13:52:16 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_default_values(t_cub3d *cub)
{
	cub->map->lines_read = 0;
	cub->map->grid = NULL;
	cub->map->map_fd = -1;
	cub->map->line_count = 0;
	cub->colors->ceiling = INT_MIN;
	cub->colors->floor = INT_MIN;
	cub->textures->east = NULL;
	cub->textures->ea_name = NULL;
	cub->textures->west = NULL;
	cub->textures->we_name = NULL;
	cub->textures->north = NULL;
	cub->textures->no_name = NULL;
	cub->textures->south = NULL;
	cub->textures->so_name = NULL;
	cub->mlx = NULL;
	cub->mlx_win = NULL;
}
