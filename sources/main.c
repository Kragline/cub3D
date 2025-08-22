/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:49:40 by armarake          #+#    #+#             */
/*   Updated: 2025/08/22 16:17:21 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3D		*cub;

	if (argc != 2)
		return (print_usage(), 1);
	cub = init_cub();
	if (!cub)
		return (print_error("Init error"), 1);
	if (!parse_the_map(argv[1], cub))
		return (free_cub(cub), 1);
	print_values(cub);
	free_cub(cub);
	return (0);
}
