/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:28:14 by armarake          #+#    #+#             */
/*   Updated: 2025/08/26 16:10:36 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

typedef struct s_cub3d	t_cub3d;

//			free
void	free_cub(t_cub3d *cub);
void	free_grid(char ***grid);

#endif