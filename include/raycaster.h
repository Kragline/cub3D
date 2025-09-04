/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:43:32 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/04 18:21:40 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>

# define TILE 64
# define FOV_ANGLE (60 * (M_PI / 180))

typedef struct s_cub3d	t_cub3d;
typedef struct s_img	t_img;

void	render_mini_map(t_cub3d *cub);
void	update_mini_map(t_cub3d *cub);
void	rect(t_img *img, int *coords, int tile, int color);
void	put_pixel(t_img *data, int x, int y, int color);
void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color); //TODO Delete this shit later
int		map_wall(t_cub3d *cub);

#endif
