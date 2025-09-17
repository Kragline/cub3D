/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:17:40 by armarake          #+#    #+#             */
/*   Updated: 2025/09/17 16:18:48 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_cub3d	t_cub3d;
typedef struct s_img	t_img;

//			init
t_cub3d	*init_cub(void);
void	init_window(t_cub3d *cub);
void	initialize_textures(t_cub3d *cub);

//			utils
void	set_default_values(t_cub3d *cub);
void	set_direction(t_cub3d *cub);
void	set_img_nulls(t_img **img);

#endif
