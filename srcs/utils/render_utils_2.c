/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:41:18 by hyap              #+#    #+#             */
/*   Updated: 2022/11/07 21:49:10 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	better_angle(double *angle)
{
	if (*angle < 0.0)
		*angle += 360.0;
	else if (*angle >= 360.0)
		*angle -= 360.0;
}

uint32_t	get_tex_color(t_img *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	return (*(uint32_t *)dst);
}
