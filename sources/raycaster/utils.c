/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:36:33 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/01 16:48:04 by nasargsy         ###   ########.fr       */
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

void	circle(t_img *img, int xc, int yc, int r)
{
	int	x;
	int	y;
	int	p;

	x = 0;
	y = r;
	p = 1 - r;
	while (x <= y)
	{
		put_pixel(img, xc + x, yc + y, 0xFF0000);
		put_pixel(img, xc - x, yc + y, 0xFF0000);
		put_pixel(img, xc + x, yc - y, 0xFF0000);
		put_pixel(img, xc - x, yc - y, 0xFF0000);
		put_pixel(img, xc + y, yc + x, 0xFF0000);
		put_pixel(img, xc - y, yc + x, 0xFF0000);
		put_pixel(img, xc + y, yc - x, 0xFF0000);
		put_pixel(img, xc - y, yc - x, 0xFF0000);
		x++;
		if (p < 0)
			p = p + 2 * x + 1;
		else
		{
			y--;
			p = p + 2 * (x - y) + 1;
		}
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
