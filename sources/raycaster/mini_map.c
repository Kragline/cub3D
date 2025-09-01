/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:28:43 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/01 17:08:35 by nasargsy         ###   ########.fr       */
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
			tile_coords[0] = j * TILE;
			tile_coords[1] = i * TILE;
			if (map[i][j] == 1)
				color = 0x000000;
			else if (map[i][j] == 0 || map[i][j] == -1)
				color = 0xFFFFFF;
			else
			{
				cub->map->player_x = j;
				cub->map->player_y = i;
				color = 0xFFFFFF;
			}
			rect(cub->img, tile_coords, TILE, color);
			j++;
		}
		i++;
	}
	circle(cub->img,
		cub->map->player_x * TILE + TILE / 2,
		cub->map->player_y * TILE + TILE / 2,
		cub->player->radius);
	draw_line(cub->img,
		cub->map->player_x * TILE + TILE / 2,
		cub->map->player_y * TILE + TILE / 2,
		cub->map->player_x * TILE + TILE / 2 + cos(cub->player->rotation_angle) * 30,
		cub->map->player_y * TILE + TILE / 2 + sin(cub->player->rotation_angle) * 30,
		0xFF0000);
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
	circle(cub->img,
		cub->map->player_x * TILE + TILE / 2,
		cub->map->player_y * TILE + TILE / 2,
		cub->player->radius);
	draw_line(cub->img,
		cub->map->player_x * TILE + TILE / 2,
		cub->map->player_y * TILE + TILE / 2,
		cub->map->player_x * TILE + TILE / 2 + cos(cub->player->rotation_angle) * 30,
		cub->map->player_y * TILE + TILE / 2 + sin(cub->player->rotation_angle) * 30,
		0xFF0000);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img_ptr, 0, 0);
}
