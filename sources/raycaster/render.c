/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:40:53 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/14 13:06:11 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_rays(t_cub3d *cub)
{
	int		i;
	t_ray	ray;

	ray.angle = cub->player->rotation_angle - ((60 * (M_PI / 180)) / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray.x = cub->player->x * TILE + TILE / 2.0f;
		ray.y = cub->player->y * TILE + TILE / 2.0f;
		while (!map_wall(cub, ray.x, ray.y))
		{
			ray.x += cos(ray.angle) * 1.0f;
			ray.y += sin(ray.angle) * 1.0f;
		}
		ray.dist = sqrt(pow(ray.x - (cub->player->x * TILE + TILE / 2.0f), 2)
				+ pow(ray.y - (cub->player->y * TILE + TILE / 2.0f), 2))
			* cos(ray.angle - cub->player->rotation_angle);
		if (fabs(ray.x - round(ray.x / TILE) * TILE)
			< fabs(ray.y - round(ray.y / TILE) * TILE))
			cub->player->is_vertical = 1;
		else
			cub->player->is_vertical = 0;
		draw_wall(cub, i, ray);
		ray.angle += (60 * (M_PI / 180)) / NUM_RAYS;
	}
}

static	int	get_cell_color(int cell)
{
	if (cell == 1)
		return (0x000000);
	else if (cell == 0 || cell == -1)
		return (0xFFFFFF);
	return (0xFFFFFF);
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
			color = get_cell_color(map[i][j]);
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

static void	get_old_coords(t_cub3d *cub, float *old_x, float *old_y)
{
	*old_x = cub->player->x;
	*old_y = cub->player->y;
}

void	render(t_cub3d *cub)
{
	float	move_step;
	float	strafe_step;
	float	old_x;
	float	old_y;

	get_old_coords(cub, &old_x, &old_y);
	cub->player->rotation_angle += cub->player->turn_direction
		* cub->player->rotation_speed;
	move_step = cub->player->walk_direction * cub->player->move_speed / TILE;
	strafe_step = cub->player->strafe_direction
		* cub->player->move_speed / TILE;
	cub->player->x += cos(cub->player->rotation_angle) * move_step;
	cub->player->x += cos(cub->player->rotation_angle + M_PI_2) * strafe_step;
	cub->player->y += sin(cub->player->rotation_angle) * move_step;
	cub->player->y += sin(cub->player->rotation_angle + M_PI_2) * strafe_step;
	if (map_wall(cub, cub->player->x * TILE, cub->player->y * TILE))
	{
		cub->player->x = old_x;
		cub->player->y = old_y;
	}
	else
	{
		cast_rays(cub);
		render_mini_map(cub);
	}
}
