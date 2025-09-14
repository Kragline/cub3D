/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:11:23 by armarake          #+#    #+#             */
/*   Updated: 2025/09/14 12:44:14 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_grid(int ***grid)
{
	int	i;

	i = 0;
	while ((*grid)[i])
	{
		free((*grid)[i]);
		i++;
	}
	free((*grid));
}

static void	free_textures(t_cub3d *cub)
{
	if (cub->textures->east)
		free_east(cub);
	if (cub->textures->west)
		free_west(cub);
	if (cub->textures->north)
		free_north(cub);
	if (cub->textures->south)
		free_south(cub);
	free(cub->textures);
}

void	free_cub(t_cub3d *cub)
{
	if (!cub)
		return ;
	if (cub->map->grid)
		free_grid(&cub->map->grid);
	if (cub->textures)
		free_textures(cub);
	if (cub->map->map_fd != -1)
		close(cub->map->map_fd);
	if (cub->colors)
		free(cub->colors);
	if (cub->map)
		free(cub->map);
	if (cub->img->img_ptr)
		mlx_destroy_image(cub->mlx, cub->img->img_ptr);
	if (cub->mlx_win)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	if (cub->img)
		free(cub->img);
	if (cub->player)
		free(cub->player);
	if (cub->mlx)
		free(cub->mlx);
	free(cub);
}
