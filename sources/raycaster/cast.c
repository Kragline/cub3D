/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:40:13 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/08 16:02:49 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_rays(t_cub3d *cub)
{
	int		i;
	int		wall_height;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	step_size;
	float	dist;

	ray_angle = cub->player->rotation_angle - (FOV_ANGLE / 2);
	step_size = 1.0f / TILE;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_x = cub->player->x;
		ray_y = cub->player->y;
		while (!map_wall(cub, ray_x, ray_y))
		{
			ray_x += cos(ray_angle) * step_size;
			ray_y += sin(ray_angle) * step_size;
		}
		dist = sqrtf((ray_x - cub->player->x) * (ray_x - cub->player->x)
				+ (ray_y - cub->player->y) * (ray_y - cub->player->y));
		dist *= cos(cub->player->rotation_angle - ray_angle);
		dist *= TILE;
		wall_height = (int)((TILE * HEIGHT) / (dist + 0.0001f));
		draw_line(cub->img, i, 	(HEIGHT - wall_height) / 2,
				i, (HEIGHT + wall_height) / 2,
				0x0000FF);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
