/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:55:10 by armarake          #+#    #+#             */
/*   Updated: 2025/09/15 13:19:25 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static float	choose_coord(t_cub3d *cub, t_ray ray)
{
	if (cub->player->is_vertical)
		return (ray.y);
	return (ray.x);
}

static t_img	*choose_texture(t_cub3d *cub, t_ray ray)
{
	t_img	*res;

	if (cub->player->is_vertical)
	{
		if (cos(ray.angle) > 0)
			res = cub->textures->west;
		else
			res = cub->textures->east;
	}
	else
	{
		if (sin(ray.angle) < 0)
			res = cub->textures->south;
		else
			res = cub->textures->north;
	}
	return (res);
}

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

void	draw_wall(t_cub3d *cub, int x, t_ray ray)
{
	int		start_y;
	int		end_y;
	int		y;
	int		distance_from_top;

	start_y = (HEIGHT / 2) - ((int)((TILE * HEIGHT) / ray.dist) / 2);
	end_y = (HEIGHT / 2) + ((int)((TILE * HEIGHT) / ray.dist) / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	y = start_y - 1;
	while (++y < end_y)
	{
		distance_from_top = y
			+ (strip_wall_height(ray.dist) / 2) - (HEIGHT / 2);
		put_pixel(cub->img, x, y, get_pixel(choose_texture(cub, ray),
				(int)choose_coord(cub, ray) % 64, distance_from_top
				* ((float)64 / strip_wall_height(ray.dist))));
	}
	draw_rest(cub, x, start_y, end_y);
}
