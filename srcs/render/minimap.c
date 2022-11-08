/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:45:09 by yang              #+#    #+#             */
/*   Updated: 2022/11/08 11:21:50 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_player(t_game *game)
{
	t_int_pos	startpx;
	int			x;
	int			y;
	
	startpx.x = (game->player_pos.pos.x0 - game->minimap.start.x) * SCALE - 2;
	startpx.y = (game->player_pos.pos.y0 - game->minimap.start.y) * SCALE - 2;

	y = -1;
	while (++y < 5)
	{
		x = -1;
		while (++x < 5)
			my_mlx_pixel_put(&(game->minimap.img), startpx.x + x, startpx.y + y, RED);
	}
}

void	draw_minimap(t_game *game)
{
	t_double_pos	dpos;
	int				color;
	int				x;
	int				y;
	
	color = 0;
	get_start_pt(game);
	dpos.y = game->minimap.start.y;
	y = 0;
	while (y < game->minimap.pxsize.y)
	{
		x = 0;
		dpos.x = game->minimap.start.x;
		while (x < game->minimap.pxsize.x)
		{
			color = get_color(game->map, dpos);
			my_mlx_pixel_put(&(game->minimap.img), x, y, color);
			dpos.x += 1.0 / SCALE;
			x++;
		}
		dpos.y +=  1.0 / SCALE;
		y++;
	}
	draw_player(game);
}