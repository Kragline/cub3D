/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:36:33 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/04 19:25:47 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rect(t_img *img, int *coords, int tile, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			put_pixel(img, coords[0] + j, coords[1] + i, color);
			j++;
		}
		i++;
	}
}

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->length + x * (data->bpp / 8));
	dst = data->pixels_ptr + offset;
	*(unsigned int *) dst = color;
}

void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		put_pixel(img, x0, y0, color);  // Draw pixel at current point

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

int	map_wall(t_cub3d *cub)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (cub->player->x < 1 || cub->player->x > cub->map->cols - 2 || cub->player->y < 1 || cub->player->y > cub->map->rows - 2)
		return (1);
	map_grid_index_x = floor(cub->player->x);
	map_grid_index_y = floor(cub->player->y);
	return (cub->map->grid[map_grid_index_y][map_grid_index_x] == 1);
}
