/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:13:14 by armarake          #+#    #+#             */
/*   Updated: 2025/08/22 15:42:56 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool	missing_values(t_cub3D *cub)
{
	if (!cub->map->grid)
		return (print_error("No map allocated"), true);
	if (cub->map->grid
		&& cub->colors->ceiling == INT_MIN && cub->colors->floor == INT_MIN
		&& !cub->textures->ea_name && !cub->textures->we_name
		&& !cub->textures->no_name && !cub->textures->so_name)
		return (print_error("No texture or color before map"), true);
	if (cub->colors->ceiling == INT_MIN)
		return (print_error("No ceiling color"), true);
	if (cub->colors->floor == INT_MIN)
		return (print_error("No floor color"), true);
	if (!cub->textures->ea_name)
		return (print_error("No east texture"), true);
	if (!cub->textures->we_name)
		return (print_error("No west texture"), true);
	if (!cub->textures->no_name)
		return (print_error("No north texture"), true);
	if (!cub->textures->so_name)
		return (print_error("No south texture"), true);
	return (false);
}
