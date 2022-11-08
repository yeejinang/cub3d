/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:11:50 by hyap              #+#    #+#             */
/*   Updated: 2022/11/08 14:33:39 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_floor_n_ceiling(t_img *img, int color, int start_y, int end_y)
{
	t_int_pos	px;
	
	px.y = start_y;
	while (px.y < end_y)
	{
		px.x = 0;
		while (px.x < WIN_WIDTH)
		{
			my_mlx_pixel_put(img, px.x, px.y, color);
			px.x++;
		}
		px.y++;
	}
}