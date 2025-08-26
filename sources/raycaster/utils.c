/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:36:33 by nasargsy          #+#    #+#             */
/*   Updated: 2025/08/26 20:24:48 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rect(t_img *img, int *coords, int tile, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			put_pixel(img, coords[0] + j, coords[1] + i, color);
			j++;
		}
		i++;
	}
}

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->length + x * (data->bpp / 8));
	dst = data->pixels_ptr + offset;
	*(unsigned int *) dst = color;
}
