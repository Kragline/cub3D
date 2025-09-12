/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:56:47 by armarake          #+#    #+#             */
/*   Updated: 2025/09/11 20:56:15 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	close_handle(t_cub3d *cub)
{
	free_cub(cub);
	exit(1);
}

static int	mouse_handle(int button, int x, int y, t_cub3d *cub)
{
	(void)button;
	(void)x;
	(void)y;
	(void)cub;
	return (0);
}

static int	key_handle(int keysym, t_cub3d *cub)
{
	if (keysym == XK_Escape)
	{
		free_cub(cub);
		exit (1);
	}
	mlx_destroy_image(cub->mlx, cub->img->img_ptr);
	cub->img->img_ptr = mlx_new_image(cub->mlx, WIDTH,
			HEIGHT);
	if (keysym == XK_w)
		cub->player->walk_direction = 1;
	else if (keysym == XK_s)
		cub->player->walk_direction = -1;
	else if (keysym == XK_a)
		cub->player->strafe_direction = -1;
	else if (keysym == XK_d)
		cub->player->strafe_direction = 1;
	else if (keysym == XK_Left)
		cub->player->turn_direction = -1;
	else if (keysym == XK_Right)
		cub->player->turn_direction = 1;
	render(cub);
	if (cub->player->walk_direction)
		cub->player->walk_direction = 0;
	if (cub->player->turn_direction)
		cub->player->turn_direction = 0;
	if (cub->player->strafe_direction)
		cub->player->strafe_direction = 0;
	return (0);
}

void	init_window(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		free_cub(cub);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cub->mlx_win)
		free_cub(cub);
	cub->img->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img->img_ptr)
		free_cub(cub);
	cub->img->pixels_ptr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bpp,
			&cub->img->length,
			&cub->img->endian);
	cub->player->x = cub->map->player_y;
	cub->player->y = cub->map->player_x;
	initialize_textures(cub);
	set_direction(cub);
	render(cub);
	mlx_hook(cub->mlx_win,
		KeyPress, KeyPressMask, key_handle, cub);
	mlx_hook(cub->mlx_win,
		ButtonPress, ButtonPressMask, mouse_handle, cub);
	mlx_hook(cub->mlx_win,
		DestroyNotify, StructureNotifyMask, close_handle, cub);
	mlx_loop(cub->mlx);
}

static bool	allocate_textures(t_cub3d *cub)
{
	cub->textures = malloc(sizeof(t_textures));
	if (!cub->textures)
		return (free_cub(cub), false);
	cub->textures->east = malloc(sizeof(t_img));
	if (!cub->textures->east)
		return (free_cub(cub), false);
	cub->textures->west = malloc(sizeof(t_img));
	if (!cub->textures->west)
		return (free_cub(cub), false);
	cub->textures->south = malloc(sizeof(t_img));
	if (!cub->textures->south)
		return (free_cub(cub), false);
	cub->textures->north = malloc(sizeof(t_img));
	if (!cub->textures->north)
		return (free_cub(cub), false);
	return (true);
}

t_cub3d	*init_cub(void)
{
	t_cub3d	*cub;

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		return (NULL);
	cub->colors = malloc(sizeof(t_colors));
	if (!cub->colors)
		return (free_cub(cub), NULL);
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		return (free_cub(cub), NULL);
	if (!allocate_textures(cub))
		return (NULL);
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		return (free_cub(cub), NULL);
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (free_cub(cub), NULL);
	set_default_values(cub);
	return (cub);
}
