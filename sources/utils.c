/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:05:01 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 22:31:41 by armarake         ###   ########.fr       */
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
		|| c == 'S' || c == 'E' || c == 'W')
		return (true);
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

void	print_error(char *message)
{
	ft_putendl_fd(RED "Error" WHITE, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

void	print_usage(void)
{
	ft_putendl_fd(RED "Error" WHITE, STDERR_FILENO);
	ft_putstr_fd("Wrong arguments.", STDERR_FILENO);
	ft_putstr_fd(" Program usage: ", STDERR_FILENO);
	ft_putendl_fd(PURPLE "./cub3D [map.cub]" WHITE, STDERR_FILENO);
	
}
