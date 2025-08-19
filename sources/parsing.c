/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:56:45 by armarake          #+#    #+#             */
/*   Updated: 2025/08/19 18:23:20 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	line_is_empty(char *line)
{
	int	i;
	
	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static bool	set_value(char *line, char **dest, t_cub3D *cub)
{
	int	i;
	int	start_index;
	
	if (*dest)
	{
		print_error("Duplicate element in map");
		free_cub(cub);
		exit(1);
	}
	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	start_index = i;
	while (line[i] && !is_space(line[i]) && line[i] != '\n')
		i++;
	*dest = ft_substr(line + start_index, 0, i - start_index);
	return (true);
}

static bool	try_parse_element(char *line, t_cub3D *cub)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
	{
		if (line[i] == '\n')
			return (false);
		i++;
	}
	if (!ft_strncmp(line + i, "NO ", 3))
		return (set_value(line + i + 2, &cub->textures->north_name, cub), true);
	else if (!ft_strncmp(line + i, "SO ", 3))
		return (set_value(line + i + 2, &cub->textures->south_name, cub), true);
	else if (!ft_strncmp(line + i, "WE ", 3))
		return (set_value(line + i + 2, &cub->textures->west_name, cub), true);
	else if (!ft_strncmp(line + i, "EA ", 3))
		return (set_value(line + i + 2, &cub->textures->east_name, cub), true);
	else if (!ft_strncmp(line + i, "F ", 2))
		return (/*set_value(line + i + 1, &cub->colors->floor, cub), */true);
	else if (!ft_strncmp(line + i, "C ", 2))
		return (/*set_value(line + i + 1, &cub->colors->ceiling, cub), */true);
	return (false);
}

static bool	looks_like_map_line(char *line)
{
	int		i;
	bool	saw_map_char;

	i = 0;
	saw_map_char = false;
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		if (is_map_char(line[i]))
			saw_map_char = true;
		else
			return (false);
		i++;
	}
	return (saw_map_char);
}

static void	parsing_error(t_cub3D *cub, t_list **map_list, char **line, char *message)
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
	close(cub->map->map_fd);
	free_cub(cub);
	free(*line);
	exit(1);
}

static void	allocate_map(t_cub3D *cub, char **line)
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
	while (*line && looks_like_map_line(*line))
	{
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = get_next_line(cub->map->map_fd);
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
		cub->map->grid[i] = ft_strdup(map_list->content);
		i++;
		tmp = map_list->next;
		free(map_list->content);
		free(map_list);
		map_list = tmp;
	}
	if (*line)
		free(*line);
	get_next_line(-1);
	cub->map->grid[cub->map->line_count] = NULL;
}

static void	read_map(t_cub3D *cub)
{
	bool	change_line;
	char	*line;
	t_state state;

	state = ST_ELEMS;
	line = NULL;
	change_line = true;
	while (state != ST_DONE)
	{
		if (change_line)
		{			
			if (line)
			{
				free(line);
				line = NULL;
			}
			line = get_next_line(cub->map->map_fd);
		}
		if (state == ST_ELEMS)
		{
			if (line_is_empty(line))
				continue;
			if (try_parse_element(line, cub))
				continue;
			if (looks_like_map_line(line))
			{
				state = ST_MAP;
				change_line = false;
				continue;
			}
			parsing_error(cub, NULL, &line, "Unknown line before map");
		}
		else if (state == ST_MAP)
		{
			allocate_map(cub, &line);
			change_line = true;
			state = ST_DONE;
		}
		else
		{
			if (!line_is_empty(line))
				parsing_error(cub, NULL, &line, "Non-empty content after map");
		}
	}
	get_next_line(-1);
}

bool	parse_the_map(char *filname, t_cub3D *cub)
{
	if (!ends_with_cub(filname))
		return (print_error("Map name must end with .cub"), false);
	cub ->map->map_fd = open(filname, O_RDONLY);
	if (cub ->map->map_fd == -1)
		return (print_error("Can't open the map"), false);
	read_map(cub);
	return (close(cub ->map->map_fd), true);
}