/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:40:13 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/11 13:19:11 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

static void	draw_rest(t_cub3d *cub, int i, int start_y, int end_y)
{
	int	y;

	y = 0;
	while (y != start_y)
	{
		put_pixel(cub->img, i, y, cub->colors->ceiling);
		y++;
	}
	y = end_y + 1;
	while (y != HEIGHT)
	{
		put_pixel(cub->img, i, y, cub->colors->floor);
		y++;
	}
}

static void	draw_wall(t_cub3d *cub, int i, int wall_height)
{
	int	start_y;
	int	end_y;

	start_y = (HEIGHT - wall_height) / 2;
	end_y = (HEIGHT + wall_height) / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	draw_line(cub->img, i, start_y, i, end_y, 0x0000FF);
	draw_rest(cub, i, start_y, end_y);
}

void	cast_rays(t_cub3d *cub)
{
	int		i;
	int		wall_height;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	dist;

	ray_angle = cub->player->rotation_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_x = cub->player->x * TILE + TILE / 2.0f;
		ray_y = cub->player->y * TILE + TILE / 2.0f;
		while (!map_wall(cub, ray_x	, ray_y))
		{
			ray_x += cos(ray_angle) * 1.0f;
			ray_y += sin(ray_angle) * 1.0f;
		}
		dist = sqrtf((ray_x - (cub->player->x * TILE + TILE / 2.0f)) *
				(ray_x - (cub->player->x * TILE + TILE / 2.0f)) +
				(ray_y - (cub->player->y * TILE + TILE / 2.0f)) *
				(ray_y - (cub->player->y * TILE + TILE / 2.0f)));
		dist *= cos(cub->player->rotation_angle - ray_angle);
		if (dist < 1.0f)
			dist = 1.0f;
		wall_height = (int)((TILE * HEIGHT) / dist);
		draw_wall(cub, i, wall_height);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
