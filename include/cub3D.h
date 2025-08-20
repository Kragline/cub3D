/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:50:38 by armarake          #+#    #+#             */
/*   Updated: 2025/08/20 13:15:43 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/Xlib.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <limits.h>

# define RED "\033[1;31m"
# define WHITE "\033[0m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"

# define WIDTH 1080
# define HEIGHT 720

typedef enum e_state
{
	ST_ELEMS,
	ST_MAP,
	ST_DONE
}	t_state;

typedef struct s_textures
{
	void	*north;
	char	*north_name;
	void	*south;
	char	*south_name;
	void	*east;
	char	*east_name;
	void	*west;
	char	*west_name;
}	t_textures;

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}	t_colors;

typedef struct s_map
{
	char	player_dir;
	int		player_x;
	int		player_y;
	int		line_count;
	int		map_fd;
	char	**grid;
}	t_map;

typedef struct s_cub3D
{
	t_textures	*textures;
	t_colors	*colors;
	t_map		*map;
	void		*mlx;
	void		*mlx_win;
}	t_cub3D;

//			utils
bool	ends_with_cub(char *filename);
void	print_error(char *message);
void	print_usage(void);
bool	is_space(char c);
bool	is_map_char(char c);
int		spawn_point_count(char *line);
char	find_spawn_point(char *line);

//			parsing
bool	parse_the_map(char *filename, t_cub3D *cub);

//			init
t_cub3D	*init_cub(void);
void	init_window(t_cub3D *cub);

//			free
void	free_cub(t_cub3D *cub);

#endif
