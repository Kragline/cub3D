/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:28:14 by armarake          #+#    #+#             */
/*   Updated: 2025/09/14 12:41:38 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

typedef struct s_cub3d	t_cub3d;

//			free
void	free_cub(t_cub3d *cub);
void	free_grid(int ***grid);

//			utils
void	free_east(t_cub3d *cub);
void	free_west(t_cub3d *cub);
void	free_north(t_cub3d *cub);
void	free_south(t_cub3d *cub);

#endif