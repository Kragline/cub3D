/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:36:33 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/14 11:43:38 by nasargsy         ###   ########.fr       */
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

int	strip_wall_height(float dist)
{
	float	distance_proj_plane;
	float	projected_wall_height;

	distance_proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	projected_wall_height = (TILE / dist) * distance_proj_plane;
	return ((int)projected_wall_height);
}

int	get_pixel(t_img *data, int x, int y)
{
	char	*dst;
	int		offset;

	offset = (y * data->length + x * (data->bpp / 8));
	dst = data->pixels_ptr + offset;
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->length + x * (data->bpp / 8));
	dst = data->pixels_ptr + offset;
	*(unsigned int *) dst = color;
}

int	map_wall(t_cub3d *cub, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	map_grid_index_x = (int)floor(x / TILE);
	map_grid_index_y = (int)floor(y / TILE);
	if (cub->player->x < 1 || cub->player->x > cub->map->cols - 2
		|| cub->player->y < 1 || cub->player->y > cub->map->rows - 2)
		return (1);
	return (cub->map->grid[map_grid_index_y][map_grid_index_x] == 1);
}
