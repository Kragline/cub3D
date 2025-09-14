/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:38:15 by armarake          #+#    #+#             */
/*   Updated: 2025/09/14 12:40:53 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_east(t_cub3d *cub)
{
	if (cub->textures->e_name)
		free(cub->textures->e_name);
	if (cub->textures->east->img_ptr)
		mlx_destroy_image(cub->mlx, cub->textures->east->img_ptr);
	free(cub->textures->east);
}

void	free_west(t_cub3d *cub)
{
	if (cub->textures->w_name)
		free(cub->textures->w_name);
	if (cub->textures->west->img_ptr)
		mlx_destroy_image(cub->mlx, cub->textures->west->img_ptr);
	free(cub->textures->west);
}

void	free_north(t_cub3d *cub)
{
	if (cub->textures->n_name)
		free(cub->textures->n_name);
	if (cub->textures->north->img_ptr)
		mlx_destroy_image(cub->mlx, cub->textures->north->img_ptr);
	free(cub->textures->north);
}

void	free_south(t_cub3d *cub)
{
	if (cub->textures->s_name)
		free(cub->textures->s_name);
	if (cub->textures->south->img_ptr)
		mlx_destroy_image(cub->mlx, cub->textures->south->img_ptr);
	free(cub->textures->south);
}
