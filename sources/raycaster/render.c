/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:19:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/13 17:20:54 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_rays(t_cub3d *cub)
{
	int		i;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	dist;

	ray_angle = cub->player->rotation_angle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray_x = cub->player->x * TILE + TILE / 2.0f;
		ray_y = cub->player->y * TILE + TILE / 2.0f;
		while (!map_wall(cub, ray_x	, ray_y))
		{
			ray_x += cos(ray_angle) * 1.0f;
			ray_y += sin(ray_angle) * 1.0f;
		}
		dist = (ray_x - (cub->player->x * TILE + TILE / 2.0f)) * cos(ray_angle)
			+ (ray_y - (cub->player->y * TILE + TILE / 2.0f)) * sin(ray_angle);
		if (fabs(ray_x - round(ray_x / TILE) * TILE) < fabs(ray_y - round(ray_y / TILE) * TILE))
			cub->player->is_vertical = 1;
		else
			cub->player->is_vertical = 0;
		if (cub->player->is_vertical)
			draw_wall(cub, i, ray_y, dist);
		else
			draw_wall(cub, i, ray_x, dist);
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

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
			tile_coords[0] = j * TILE * 0.2;
			tile_coords[1] = i * TILE * 0.2;
			if (map[i][j] == 1)
				color = 0x000000;
			else if (map[i][j] == 0 || map[i][j] == -1)
				color = 0xFFFFFF;
			else
				color = 0xFFFFFF;
			rect(cub->img, tile_coords, TILE * 0.2, color);
			j++;
		}
		i++;
	}
	tile_coords[0] = cub->player->x * TILE * 0.2;
	tile_coords[1] = cub->player->y * TILE * 0.2;
	rect(cub->img, tile_coords, TILE * 0.2, 0xFF0000);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img_ptr, 0, 0);
}

void	render(t_cub3d *cub)
{
	float	move_step;
	float	strafe_step;
	float	oldX;
	float	oldY;

	oldX = cub->player->x;
	oldY = cub->player->y;
	cub->player->rotation_angle += cub->player->turn_direction * cub->player->rotation_speed;
	move_step = cub->player->walk_direction * cub->player->move_speed / TILE;
	strafe_step = cub->player->strafe_direction * cub->player->move_speed / TILE;
	cub->player->x += cos(cub->player->rotation_angle) * move_step;
	cub->player->x += cos(cub->player->rotation_angle + M_PI_2) * strafe_step;
	cub->player->y += sin(cub->player->rotation_angle) * move_step;
	cub->player->y += sin(cub->player->rotation_angle + M_PI_2) * strafe_step;
	if (map_wall(cub, cub->player->x * TILE, cub->player->y * TILE))
	{
		cub->player->x = oldX;
		cub->player->y = oldY;
	}
	cast_rays(cub);
	render_mini_map(cub);
}
