/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:56:47 by armarake          #+#    #+#             */
/*   Updated: 2025/08/29 14:30:19 by nasargsy         ###   ########.fr       */
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
	return (0);
}

void	init_window(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		free_cub(cub);
	cub->mlx_win = mlx_new_window(cub->mlx, cub->map->cols * 64,
			cub->map->rows * 64, "cub3D");
	if (!cub->mlx_win)
		free_cub(cub);
	cub->img->img_ptr = mlx_new_image(cub->mlx, cub->map->cols * 64,
			cub->map->rows * 64);
	if (!cub->img->img_ptr)
		free_cub(cub);
	cub->img->pixels_ptr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bpp,
			&cub->img->length,
			&cub->img->endian);
	render_mini_map(cub);
	mlx_hook(cub->mlx_win,
		KeyPress, KeyPressMask, key_handle, cub);
	mlx_hook(cub->mlx_win,
		ButtonPress, ButtonPressMask, mouse_handle, cub);
	mlx_hook(cub->mlx_win,
		DestroyNotify, StructureNotifyMask, close_handle, cub);
	mlx_loop(cub->mlx);
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
	cub->textures = malloc(sizeof(t_textures));
	if (!cub->textures)
		return (free_cub(cub), NULL);
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		return (free_cub(cub), NULL);
	set_default_values(cub);
	return (cub);
}
