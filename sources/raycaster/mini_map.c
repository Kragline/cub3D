/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:28:43 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/04 19:26:48 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_mini_map(t_cub3d *cub)
{
	int		i;
	int		j;
	int		tile_coords[2];
	int		color;
	int		**map;

	map = cub->map->grid;
	i = 0;
	while (i < cub->map->rows)
	{
		j = 0;
		while (j < cub->map->cols)
		{
			tile_coords[0] = j * TILE * 0.3;
			tile_coords[1] = i * TILE * 0.3;
			if (map[i][j] == 1)
				color = 0x000000;
			else if (map[i][j] == 0 || map[i][j] == -1)
				color = 0xFFFFFF;
			else
			{
				cub->player->x = j;
				cub->player->y = i;
				color = 0xFFFFFF;
			}
			rect(cub->img, tile_coords, TILE * 0.3, color);
			j++;
		}
		i++;
	}
	tile_coords[0] = cub->player->x * TILE * 0.3;
	tile_coords[1] = cub->player->y * TILE * 0.3;
	rect(cub->img, tile_coords, TILE * 0.3, 0xFF0000);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img_ptr, 0, 0);
}

void	update_mini_map(t_cub3d *cub)
{
	int		i;
	int		j;
	int		tile_coords[2];
	int		color;
	int		**map;

	map = cub->map->grid;
	i = 0;
	while (i < cub->map->rows)
	{
		j = 0;
		while (j < cub->map->cols)
		{
			tile_coords[0] = j * TILE * 0.3;
			tile_coords[1] = i * TILE * 0.3;
			if (map[i][j] == 1)
				color = 0x000000;
			else
				color = 0xFFFFFF;
			rect(cub->img, tile_coords, TILE * 0.3, color);
			j++;
		}
		i++;
	}
	tile_coords[0] = cub->player->x * TILE * 0.3;
	tile_coords[1] = cub->player->y * TILE * 0.3;
	rect(cub->img, tile_coords, TILE * 0.3, 0xFF0000);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img_ptr, 0, 0);
}
