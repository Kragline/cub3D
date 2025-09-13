/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:14:45 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/13 18:03:35 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_img	*choose_texture(t_cub3d *cub, float ray_angle)
{
	t_img	*res;
	if (cub->player->is_vertical)
			res = cub->textures->north;
	else
			res = cub->textures->east;
	(void)ray_angle;
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

void	draw_wall(t_cub3d *cub, int x, float coord, t_ray ray)
{
	int		start_y;
	int		end_y;
	int		y;
	int		distance_from_top;
	t_img	*texture;

	start_y = (HEIGHT / 2) - ((int)((TILE * HEIGHT) / ray.dist) / 2);
	end_y = (HEIGHT / 2) + ((int)((TILE * HEIGHT) / ray.dist) / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	y = start_y;
	texture = choose_texture(cub, ray.angle);
	while (y < end_y)
	{
		distance_from_top = y + (strip_wall_height(ray.dist) / 2) - (HEIGHT / 2);
		put_pixel(cub->img, x, y, get_pixel(texture,
					(int)coord % 64, distance_from_top * ((float)64 / strip_wall_height(ray.dist))));
		y++;
	}
	draw_rest(cub, x, start_y, end_y);
}
