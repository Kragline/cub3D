/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:56:47 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 23:46:11 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	close_handle(t_cub3D *cub)
{
	free_cub(cub);
	exit(1);
}

static int	mouse_handle(int button, int x, int y, t_cub3D *cub)
{
	(void)button;
	(void)x;
	(void)y;
	(void)cub;
	return (0);
}

static int	key_handle(int keysym, t_cub3D *cub)
{
	if (keysym == XK_Escape)
	{
		free_cub(cub);
		exit (1);
	}
	return (0);
}

t_cub3D	*init_cub(void)
{
	t_cub3D	*cub;

	cub = malloc(sizeof(t_cub3D));
	if (!cub)
		return (NULL);
	cub->colors = malloc(sizeof(t_colors));
	if (!cub->colors)
		return (free(cub), NULL);
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		return (free(cub->colors), free(cub), NULL);
	cub->textures = malloc(sizeof(t_textures));
	if (!cub->textures)
		return (free(cub->map), free(cub->colors), free(cub), NULL);
	cub->map->grid = NULL;
	cub->map->line_count = 0;
	cub->textures->east = NULL;
	cub->textures->east_name = NULL;
	cub->textures->west = NULL;
	cub->textures->west_name = NULL;
	cub->textures->north = NULL;
	cub->textures->north_name = NULL;
	cub->textures->south = NULL;
	cub->textures->south_name = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (free(cub->map), free(cub->colors), free(cub), NULL);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cub->mlx_win)
		return (mlx_destroy_display(cub->mlx), free(cub->map), free(cub->colors), free(cub), NULL);
	mlx_hook(cub->mlx_win,
			KeyPress, KeyPressMask,
			key_handle, cub);
	mlx_hook(cub->mlx_win,
			ButtonPress, ButtonPressMask,
			mouse_handle, cub);
	mlx_hook(cub->mlx_win,
			DestroyNotify, StructureNotifyMask,
			close_handle, cub);
	mlx_loop(cub->mlx);
	return (cub);
}
