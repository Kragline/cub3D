/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:00:14 by armarake          #+#    #+#             */
/*   Updated: 2025/09/11 15:10:22 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_int_0_255(char *line, int *i)
{
	long	value;
	int		digit_start;

	value = 0;
	if (line[*i] && line[*i] == ',')
		(*i)++;
	if (line[*i] == '\n')
		return (-1);
	digit_start = *i;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (line[*i] && !ft_isdigit(line[*i]))
		return (-1);
	while (line[*i] && ft_isdigit(line[*i]))
	{
		value = value * 10 + (line[*i] - '0');
		if (value > 255)
			return (-1);
		(*i)++;
	}
	if (*i == digit_start)
		return (-1);
	return ((int)value);
}

void	get_color(char **line, int *i, int *col, t_cub3d *cub)
{
	while ((*line)[*i] && is_space((*line)[*i]))
		(*i)++;
	*col = parse_int_0_255(*line, i);
	if (*col < 0)
		parsing_error(cub, NULL, line, "Wrong value for color");
}

void	texture_name_check(char **name, char **line, t_cub3d *cub)
{
	if (!ends_with_xpm(*name))
	{
		free(*name);
		parsing_error(cub, NULL, line, "Texture must have .xpm extension");
	}
}

void	texture_checks(int *i, char **line, t_cub3d *cub)
{
	if (!(*line)[*i] || (*line)[*i] == '\n')
		parsing_error(cub, NULL, line, "Wrong value for texture");
	while ((*line)[*i] && is_space((*line)[*i]))
		(*i)++;
	if (!(*line)[*i] || (*line)[*i] == '\n')
		parsing_error(cub, NULL, line, "Wrong value for texture");
}

bool	ends_with_xpm(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".xpm", 4) == 0);
}
