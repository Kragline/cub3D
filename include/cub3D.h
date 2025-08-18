/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:50:38 by armarake          #+#    #+#             */
/*   Updated: 2025/08/18 17:28:00 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>

# define RED "\033[1;31m"
# define WHITE "\033[0m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
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

//			validate
bool	valiate(char *filname);

//			init
t_cub3D	*init_cub(void);

//			free
void	free_cub(t_cub3D *cub);

#endif