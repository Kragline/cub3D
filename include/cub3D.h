/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:50:38 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 20:22:12 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "init.h"
# include "parsing.h"
# include "cleanup.h"
# include "raycaster.h"

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
	char	*no_name;
	void	*south;
	char	*so_name;
	void	*east;
	char	*ea_name;
	void	*west;
	char	*we_name;
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
	int		cols;
	int		rows;
	int		lines_read;
	int		map_fd;
	int		**grid;
	char	*filename;
}	t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_cub3d
{
	t_textures	*textures;
	t_colors	*colors;
	t_map		*map;
	t_img		*img;
	void		*mlx;
	void		*mlx_win;
}	t_cub3d;

#endif
