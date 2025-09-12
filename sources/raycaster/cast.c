/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:40:13 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/12 18:07:33 by nasargsy         ###   ########.fr       */
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

static int	get_pixel(t_img *data, int x, int y)
{
	char	*dst;
	int		offset;

	offset = (y * data->length + x * (data->bpp / 8));
	dst = data->pixels_ptr + offset;
	return (*(unsigned int *)dst);
}

static void	draw_wall(t_cub3d *cub, int x, float ray_x, int wall_height)
{
	int	start_y;
	int	end_y;
	int	y;
	int	distance_from_top;

	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	y = start_y;
	while (y < end_y)
	{
		distance_from_top = y + (wall_height / 2) - (HEIGHT / 2);
		put_pixel(cub->img, x, y, get_pixel(cub->textures->west,
					(int)ray_x % 64, distance_from_top * ((float)64 / wall_height)));
		y++;
	}
	draw_rest(cub, x, start_y, end_y);
}

static int	strip_wall_height(float dist)
{
	float	distance_proj_plane;
	float	projected_wall_height;

	distance_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	projected_wall_height = (TILE / dist) * distance_proj_plane;
	return ((int)projected_wall_height);
}

void	cast_rays(t_cub3d *cub)
{
	int		i;
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
		dist = (ray_x - (cub->player->x * TILE + TILE / 2.0f)) * cos(ray_angle)
			+ (ray_y - (cub->player->y * TILE + TILE / 2.0f)) * sin(ray_angle);
		draw_wall(cub, i, ray_x, strip_wall_height(dist));
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
