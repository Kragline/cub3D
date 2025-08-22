/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:11:17 by armarake          #+#    #+#             */
/*   Updated: 2025/08/22 15:12:09 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	allocate_map(t_cub3D *cub, char **line)
{
	int		i;
	int		line_spawn_count;
	char	spawn_dir;
	t_list	*tmp;
	t_list	*map_list;

	i = 0;
	tmp = NULL;
	spawn_dir = '\0';
	map_list = ft_lstnew(ft_strdup(*line));
	(cub->map->line_count)++;
	while (*line && is_map_line(*line))
	{
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = get_next_line(cub->map->map_fd);
		if (!is_map_line(*line))
		{
			get_next_line(-1);
			free(*line);
			line = NULL;
			break ;
		}
		if (*line)
		{
			line_spawn_count = spawn_point_count(*line);
			if (line_spawn_count > 1 || (line_spawn_count > 0 && spawn_dir))
				parsing_error(cub, &map_list, line, "Multiple spawn points");
			else if (line_spawn_count == 1)
				spawn_dir = find_spawn_point(*line);
			ft_lstadd_back(&map_list, ft_lstnew(ft_strdup(*line)));
			(cub->map->line_count)++;
		}
	}
	cub->map->player_dir = spawn_dir;
	cub->map->grid = malloc(sizeof(char *) * (cub->map->line_count + 1));
	while (map_list)
	{
		cub->map->grid[i] = ft_strtrim(map_list->content, "\t\n\v\f ");
		i++;
		tmp = map_list->next;
		free(map_list->content);
		free(map_list);
		map_list = tmp;
	}
	cub->map->grid[cub->map->line_count] = NULL;
}
