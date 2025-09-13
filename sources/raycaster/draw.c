/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:14:45 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/13 17:15:37 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rest(t_cub3d *cub, int i, int start_y, int end_y)
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

void	draw_wall(t_cub3d *cub, int x, float coord, float dist)
{
	int	start_y;
	int	end_y;
	int	y;
	int	distance_from_top;
	int	wall_height;

	wall_height = (int)((TILE * HEIGHT) / dist);
	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	y = start_y;
	while (y < end_y)
	{
		distance_from_top = y + (strip_wall_height(dist) / 2) - (HEIGHT / 2);
		if (cub->player->is_vertical)
		put_pixel(cub->img, x, y, get_pixel(cub->textures->south,
					(int)coord % 64, distance_from_top * ((float)64 / strip_wall_height(dist))));
		else
		put_pixel(cub->img, x, y, get_pixel(cub->textures->west,
					(int)coord % 64, distance_from_top * ((float)64 / strip_wall_height(dist))));
		y++;
	}
	draw_rest(cub, x, start_y, end_y);
}
