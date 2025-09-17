/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:05:01 by armarake          #+#    #+#             */
/*   Updated: 2025/09/17 16:08:10 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

char	find_spawn_point(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			return (line[i]);
		i++;
	}
	return ('\0');
}

int	spawn_point_count(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			count++;
		i++;
	}
	return (count);
}

bool	missing_elements(t_cub3d *cub)
{
	if (cub->colors->ceiling == INT_MIN && cub->colors->floor == INT_MIN
		&& !cub->textures->e_name && !cub->textures->w_name
		&& !cub->textures->n_name && !cub->textures->s_name)
		return (print_error("Map before colors and textures"), true);
	if (cub->colors->ceiling == INT_MIN)
		return (print_error("No ceiling color before map"), true);
	if (cub->colors->floor == INT_MIN)
		return (print_error("No floor color before map"), true);
	if (!cub->textures->e_name)
		return (print_error("No east texture before map"), true);
	if (!cub->textures->w_name)
		return (print_error("No west texture before map"), true);
	if (!cub->textures->n_name)
		return (print_error("No north texture before map"), true);
	if (!cub->textures->s_name)
		return (print_error("No south texture before map"), true);
	return (false);
}
