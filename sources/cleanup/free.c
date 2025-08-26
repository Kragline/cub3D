/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:11:23 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 17:36:23 by nasargsy         ###   ########.fr       */
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
	if (cub->textures->ea_name)
		free(cub->textures->ea_name);
	if (cub->textures->we_name)
		free(cub->textures->we_name);
	if (cub->textures->no_name)
		free(cub->textures->no_name);
	if (cub->textures->so_name)
		free(cub->textures->so_name);
	if (cub->textures)
		free(cub->textures);
}

void	free_cub(t_cub3d *cub)
{
	if (!cub)
		return ;
	if (cub->map->grid)
		free_grid(&cub->map->grid);
	free_textures(cub);
	if (cub->map->map_fd != -1)
		close(cub->map->map_fd);
	if (cub->colors)
		free(cub->colors);
	if (cub->map)
		free(cub->map);
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	if (cub->mlx_win)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
}
