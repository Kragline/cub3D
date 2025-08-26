/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:11:17 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 15:16:22 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	break_the_loop(char **line, t_cub3d *cub)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	*line = get_next_line(cub->map->map_fd);
	cub->map->lines_read++;
	if (!is_map_line(*line))
	{
		get_next_line(-1);
		free(*line);
		*line = NULL;
		return (true);
	}
	return (false);
}

static void	find_player_spawn(char **line, char *spawn_dir,
				t_list **map_list, t_cub3d *cub)
{
	int	len;
	int	line_spawn_count;

	line_spawn_count = spawn_point_count(*line);
	if (line_spawn_count > 1 || (line_spawn_count > 0 && *spawn_dir))
		parsing_error(cub, map_list, line, "Multiple spawn points");
	else if (line_spawn_count == 1)
		*spawn_dir = find_spawn_point(*line);
	len = safe_strlen(*line);
	if ((*line)[len - 1] == '\n')
	{
		(*line)[len - 1] = '\0';
		len--;
	}
	if (len > cub->map->cols)
		cub->map->cols = len;
	ft_lstadd_back(map_list, ft_lstnew(ft_strdup(*line)));
	(cub->map->rows)++;
}

char	*normalized_line(char *line, int max_width)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(max_width + 1);
	while (line[i] && line[i] == ' ')
	{
		new[i] = '-';
		i++;
	}
	while (line[i])
	{
		if (line[i] == ' ')
			new[i] = '0';
		else
			new[i] = line[i];
		i++;
	}
	while (i < max_width)
	{
		new[i] = '-';
		i++;
	}
	new[max_width] = '\0';
	return (new);
}

static void	from_list_to_grid(t_list **map_list, t_cub3d *cub)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = NULL;
	cub->map->grid = malloc(sizeof(char *) * (cub->map->rows + 1));
	while (*map_list)
	{
		cub->map->grid[i] = normalized_line((*map_list)->content, cub->map->cols);
		i++;
		tmp = (*map_list)->next;
		free((*map_list)->content);
		free(*map_list);
		(*map_list) = tmp;
	}
	cub->map->grid[cub->map->rows] = NULL;
}

void	allocate_map(t_cub3d *cub, char **line)
{
	char	spawn_dir;
	t_list	*map_list;

	spawn_dir = '\0';
	cub->map->cols = safe_strlen(*line);
	if ((*line)[cub->map->cols - 1] == '\n')
	{
		(*line)[cub->map->cols - 1] = '\0';
		(cub->map->cols)--;
	}
	map_list = ft_lstnew(ft_strdup(*line));
	(cub->map->rows)++;
	while (*line && is_map_line(*line))
	{
		if (break_the_loop(line, cub))
			break ;
		if (*line)
			find_player_spawn(line, &spawn_dir, &map_list, cub);
	}
	cub->map->player_dir = spawn_dir;
	from_list_to_grid(&map_list, cub);
}
