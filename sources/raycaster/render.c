/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:19:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/11 13:43:19 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(t_cub3d *cub)
{
	float	move_step;
	float	strafe_step;
	float	oldX;
	float	oldY;

	oldX = cub->player->x;
	oldY = cub->player->y;
	cub->player->rotation_angle += cub->player->turn_direction * cub->player->rotation_speed;
	move_step = cub->player->walk_direction * cub->player->move_speed / TILE;
	strafe_step = cub->player->strafe_direction * cub->player->move_speed / TILE;
	cub->player->x += cos(cub->player->rotation_angle) * move_step;
	cub->player->x += cos(cub->player->rotation_angle + M_PI_2) * strafe_step;
	cub->player->y += sin(cub->player->rotation_angle) * move_step;
	cub->player->y += sin(cub->player->rotation_angle + M_PI_2) * strafe_step;
	if (map_wall(cub, cub->player->x * TILE, cub->player->y * TILE))
	{
		cub->player->x = oldX;
		cub->player->y = oldY;
	}
	cast_rays(cub);
	render_mini_map(cub);
}
