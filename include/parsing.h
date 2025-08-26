/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:20:12 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 20:10:53 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <X11/Xlib.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <limits.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_cub3d	t_cub3d;

//			parsing
bool	parse_the_map(char *filename, t_cub3d *cub);

//			allocate map
void	allocate_map(t_cub3d *cub, char **line);

//			element parsing
bool	try_parse_element(char **line, t_cub3d *cub);

//			parsing checks
bool	line_is_empty(char *line);
bool	is_map_line(char *line);
bool	is_all_wall(char *line);
bool	file_is_empty(char *filname);

//			parsing utils
bool	is_space(char c);
bool	is_map_char(char c);
int		spawn_point_count(char *line);
char	find_spawn_point(char *line);

//			additional
bool	missing_values(t_cub3d *cub);
bool	ends_with_cub(char *filename);
int		safe_strlen(char *str);

//			dfs
bool	map_is_closed(t_cub3d *cub);

//			prints
void	print_error(char *message);
void	print_usage(void);
void	print_values(t_cub3d *cub);
void	parsing_error(t_cub3d *cub, t_list **map_list,
			char **line, char *message);

#endif