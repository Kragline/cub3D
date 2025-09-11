/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:13:14 by armarake          #+#    #+#             */
/*   Updated: 2025/09/11 14:24:58 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_direction(t_cub3d *cub)
{
	if (cub->map->player_dir == 'N')
		cub->player->rotation_angle = M_PI * 1.5;
	else if (cub->map->player_dir == 'S')
		cub->player->rotation_angle = M_PI / 2;
	else if (cub->map->player_dir == 'E')
		cub->player->rotation_angle = M_PI * 2;
	else if (cub->map->player_dir == 'W')
		cub->player->rotation_angle = M_PI;
}

void	set_default_values(t_cub3d *cub)
{
	cub->map->rows = 0;
	cub->map->grid = NULL;
	cub->map->map_fd = -1;
	cub->map->player_x = INT_MIN;
	cub->map->player_y = INT_MIN;
	cub->map->lines_read = 0;
	cub->colors->ceiling = INT_MIN;
	cub->colors->floor = INT_MIN;
	cub->textures->east = NULL;
	cub->textures->west = NULL;
	cub->textures->north = NULL;
	cub->textures->south = NULL;
	cub->mlx = NULL;
	cub->mlx_win = NULL;
	cub->img->img_ptr = NULL;
	cub->player->x = 0;
	cub->player->y = 0;
	cub->player->turn_direction = 0;
	cub->player->walk_direction = 0;
	cub->player->strafe_direction = 0;
	cub->player->move_speed = 5;
	cub->player->rotation_speed = 5 * (M_PI / 180);
}
