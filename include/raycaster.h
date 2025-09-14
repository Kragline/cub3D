/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:43:32 by nasargsy          #+#    #+#             */
/*   Updated: 2025/09/14 13:06:35 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>

# define TILE 64
# define NUM_RAYS WIDTH

typedef struct s_cub3d	t_cub3d;
typedef struct s_img	t_img;

typedef struct s_ray
{
	float	x;
	float	y;
	float	angle;
	float	dist;
}	t_ray;

void	render(t_cub3d *cub);
void	render_mini_map(t_cub3d *cub);
void	rect(t_img *img, int *coords, int tile, int color);
void	put_pixel(t_img *data, int x, int y, int color);
void	cast_rays(t_cub3d *cub);
int		map_wall(t_cub3d *cub, float x, float y);
int		get_pixel(t_img *data, int x, int y);
int		strip_wall_height(float dist);
void	draw_wall(t_cub3d *cub, int x, t_ray ray);

#endif
