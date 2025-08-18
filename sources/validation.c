/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:56:45 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 17:43:03 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	valiate(char *filname)
{
	int		map_fd;

	if (!ends_with_cub(filname))
		return (print_error("Map name must end with .cub"), false);
	map_fd = open(filname, O_RDONLY);
	if (map_fd == -1)
		return (print_error("Can't open the map"), false);
	
	return (close(map_fd), true);
}