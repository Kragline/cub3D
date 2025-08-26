/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:28:43 by nasargsy          #+#    #+#             */
/*   Updated: 2025/08/26 20:24:07 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_mini_map(t_cub3d *cub)
{
	int		i;
	int		j;
	int		tile_coords[2];
	int		color;
	int		**map = cub->map->grid;
	i = 0;
	while (i < cub->map->rows)
	{
		j = 0;
		while (j < cub->map->cols)
		{
			tile_coords[0] = j * TILE;
			tile_coords[1] = i * TILE;
			if (map[i][j] == 1)
				color = 0x000000;
			else
				color = 0xFFFFFF;
			rect(cub->img, tile_coords, TILE, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img_ptr, 0, 0);
}
