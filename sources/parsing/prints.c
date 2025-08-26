/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:34:09 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 16:25:14 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	print_values(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (cub->map->grid[i])
	{
		ft_printf("%s\n", cub->map->grid[i]);
		i++;
	}
	ft_printf("%d\n", cub->map->cols);
	ft_printf("%s\n", cub->textures->ea_name);
	ft_printf("%s\n", cub->textures->we_name);
	ft_printf("%s\n", cub->textures->no_name);
	ft_printf("%s\n", cub->textures->so_name);
	ft_printf("%d\n", cub->colors->floor);
	ft_printf("%d\n", cub->colors->ceiling);
	ft_printf("%c\n", cub->map->player_dir);
}

static void	print_help_message(char *line, char *filename, int lines_read)
{
	ft_putstr_fd("At ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putnbr_fd(lines_read, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
}

void	parsing_error(t_cub3d *cub, t_list **map_list,
			char **line, char *message)
{
	t_list	*tmp;

	if (map_list && *map_list)
	{
		while (*map_list)
		{
			tmp = (*map_list)->next;
			free((*map_list)->content);
			free((*map_list));
			*map_list = tmp;
		}
	}
	get_next_line(-1);
	print_error(message);
	if (line && *line)
		print_help_message(*line, cub->map->filename, cub->map->rows);
	close(cub->map->map_fd);
	free_cub(cub);
	if (line && *line)
		free(*line);
	exit(1);
}
