/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:43:32 by nasargsy          #+#    #+#             */
/*   Updated: 2025/08/26 15:44:29 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>

# define TILE 64
# define ROWS 8
# define COLS 8

# define MAP_WIDTH COLS * TILE
# define MAP_HEIGHT ROWS * TILE

typedef struct s_cub3d		t_cub3d;
typedef struct s_img			t_img;

void	render_mini_map(t_cub3d *cub);
void	rect(t_img img, int *coords, int tile, int color);
void	put_pixel(t_img *data, int x, int y, int color);

#endif
