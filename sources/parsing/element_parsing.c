/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:03:17 by armarake          #+#    #+#             */
/*   Updated: 2025/09/02 17:16:23 by armarake         ###   ########.fr       */
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
	texture_checks(&i, line, cub);
	start_index = i;
	while ((*line)[i] && !is_space((*line)[i]) && (*line)[i] != '\n')
		i++;
	texture_name = ft_substr((*line) + start_index, 0, i - start_index);
	if (!ends_with_xpm(texture_name))
	{
		free(texture_name);
		parsing_error(cub, NULL, line, "Texture must have .xpm extension");
	}
	*dest = mlx_xpm_file_to_image(cub->mlx, texture_name, &width, &height);
	free(texture_name);
	if (!*dest)
		parsing_error(cub, NULL, line, "Failed to create mlx image");
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
	if (!valid_commas(*line, index))
		parsing_error(cub, NULL, line, "Color must contain exactly 2 commas");
	if (*dest != INT_MIN)
		parsing_error(cub, NULL, line, "Duplicate element in map");
	i = index;
	get_color(line, &i, &r, cub);
	get_color(line, &i, &g, cub);
	get_color(line, &i, &b, cub);
	while ((*line)[i] && is_space((*line)[i]))
		i++;
	if ((*line)[i] && (*line)[i] != '\n')
		parsing_error(cub, NULL, line, "Extra characters after color");
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
