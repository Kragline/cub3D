/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:13:14 by armarake          #+#    #+#             */
/*   Updated: 2025/09/17 16:15:25 by armarake         ###   ########.fr       */
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
	cub->textures->n_name = NULL;
	cub->textures->w_name = NULL;
	cub->textures->e_name = NULL;
	cub->textures->s_name = NULL;
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

static void	initialize_sides(t_cub3d *cub)
{
	int		width;
	int		height;

	cub->textures->east->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, cub->textures->e_name,
			&width, &height);
	if (!cub->textures->east->img_ptr)
		parsing_error(cub, NULL, NULL, "Failed to create east image");
	cub->textures->east->pixels_ptr
		= mlx_get_data_addr(cub->textures->east->img_ptr,
			&(cub->textures->east->bpp),
			&(cub->textures->east->length),
			&(cub->textures->east->endian));
	cub->textures->west->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, cub->textures->w_name,
			&width, &height);
	if (!cub->textures->west->img_ptr)
		parsing_error(cub, NULL, NULL, "Failed to create west image");
	cub->textures->west->pixels_ptr
		= mlx_get_data_addr(cub->textures->west->img_ptr,
			&(cub->textures->west->bpp),
			&(cub->textures->west->length),
			&(cub->textures->west->endian));
}

void	initialize_textures(t_cub3d *cub)
{
	int		width;
	int		height;

	initialize_sides(cub);
	cub->textures->north->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, cub->textures->n_name,
			&width, &height);
	if (!cub->textures->north->img_ptr)
		parsing_error(cub, NULL, NULL, "Failed to create north image");
	cub->textures->north->pixels_ptr
		= mlx_get_data_addr(cub->textures->north->img_ptr,
			&(cub->textures->north->bpp),
			&(cub->textures->north->length),
			&(cub->textures->north->endian));
	cub->textures->south->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, cub->textures->s_name,
			&width, &height);
	if (!cub->textures->south->img_ptr)
		parsing_error(cub, NULL, NULL, "Failed to create south image");
	cub->textures->south->pixels_ptr
		= mlx_get_data_addr(cub->textures->south->img_ptr,
			&(cub->textures->south->bpp),
			&(cub->textures->south->length),
			&(cub->textures->south->endian));
}

void	set_img_nulls(t_img **img)
{
	(*img)->img_ptr = NULL;
	(*img)->pixels_ptr = NULL;
	(*img)->bpp = 0;
	(*img)->length = 0;
	(*img)->endian = 0;
}
