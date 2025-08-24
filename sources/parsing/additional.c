/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:10:55 by armarake          #+#    #+#             */
/*   Updated: 2025/08/24 13:52:16 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	missing_values(t_cub3d *cub)
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

bool	ends_with_cub(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}
