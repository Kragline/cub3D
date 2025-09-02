/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:03:17 by armarake          #+#    #+#             */
/*   Updated: 2025/09/02 15:40:36 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parse_texture(char **line, int index, void **dest, t_cub3d *cub)
{
	int		i;
	int		width;
	int		height;
	int		start_index;
	char	*texture_name;

	if (*dest)
		parsing_error(cub, NULL, line, "Duplicate element in map");
	i = index;
	if (!(*line)[i] || (*line)[i] == '\n')
		parsing_error(cub, NULL, line, "Wrong value for texture");
	while ((*line)[i] && is_space((*line)[i]))
		i++;
	if (!(*line)[i] || (*line)[i] == '\n')
		parsing_error(cub, NULL, line, "Wrong value for texture");
	start_index = i;
	while ((*line)[i] && !is_space((*line)[i]) && (*line)[i] != '\n')
		i++;
	texture_name = ft_substr((*line) + start_index, 0, i - start_index);
	*dest = mlx_xpm_file_to_image(cub->mlx, texture_name, &width, &height);
	free(texture_name);
	if (!*dest)
		parsing_error(cub, NULL, line, "Failed to create mlx image");
}

static int	parse_int_0_255(char *line, int *i)
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

static void	get_color(char **line, int *i, int *col, t_cub3d *cub)
{
	while ((*line)[*i] && is_space((*line)[*i]))
		(*i)++;
	*col = parse_int_0_255(*line, i);
	if (*col < 0)
		parsing_error(cub, NULL, line, "Wrong value for color");
}

static void	parse_color(char **line, int index, int *dest, t_cub3d *cub)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = INT_MIN;
	g = INT_MIN;
	b = INT_MIN;
	if (*dest != INT_MIN)
		parsing_error(cub, NULL, line, "Duplicate element in map");
	i = index;
	get_color(line, &i, &r, cub);
	get_color(line, &i, &g, cub);
	get_color(line, &i, &b, cub);
	if (r == INT_MIN || g == INT_MIN || b == INT_MIN)
		parsing_error(cub, NULL, line, "Color values are not complete");
	*dest = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

bool	try_parse_element(char **line, t_cub3d *cub)
{
	int	i;

	i = 0;
	while ((*line)[i] && is_space((*line)[i]))
	{
		if ((*line)[i] == '\n')
			return (false);
		i++;
	}
	if (!ft_strncmp(*line + i, "NO ", 3))
		return (parse_texture(line, i + 2, &cub->textures->north, cub), true);
	else if (!ft_strncmp(*line + i, "SO ", 3))
		return (parse_texture(line, i + 2, &cub->textures->south, cub), true);
	else if (!ft_strncmp(*line + i, "WE ", 3))
		return (parse_texture(line, i + 2, &cub->textures->west, cub), true);
	else if (!ft_strncmp(*line + i, "EA ", 3))
		return (parse_texture(line, i + 2, &cub->textures->east, cub), true);
	else if (!ft_strncmp(*line + i, "F ", 2))
		return (parse_color(line, i + 1, &cub->colors->floor, cub), true);
	else if (!ft_strncmp(*line + i, "C ", 2))
		return (parse_color(line, i + 1, &cub->colors->ceiling, cub), true);
	return (false);
}
