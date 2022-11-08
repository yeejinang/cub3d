/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:50:56 by hyap              #+#    #+#             */
/*   Updated: 2022/11/08 12:34:29 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void set_player_direction(t_game *game)
{
	game->player_pos.pos.x1 = game->player_pos.pos.x0 + \
								cos(deg_to_rad(game->player_pos.angle));
	game->player_pos.pos.y1 = game->player_pos.pos.y0 - \
								sin(deg_to_rad(game->player_pos.angle));
}

void get_start_pt(t_game *game)
{
	t_double_pos	dist;
	t_double_pos	player_pos;
	
	dist.x = (double)game->minimap.size.x / 2;
	dist.y = (double)game->minimap.size.y / 2;
	player_pos.x = game->player_pos.pos.x0;
	player_pos.y = game->player_pos.pos.y0;
	if (player_pos.x - dist.x < 0.0)
		game->minimap.start.x = 0.0;
	else if (player_pos.x + dist.x > game->map_size.x)
		game->minimap.start.x = game->map_size.x - game->minimap.size.x;
	else
		game->minimap.start.x = player_pos.x - dist.x;
	if (player_pos.y - dist.y < 0.0)
		game->minimap.start.y = 0.0;
	else if (player_pos.y + dist.y > game->map_size.y)
		game->minimap.start.y = game->map_size.y - game->minimap.size.y;
	else
		game->minimap.start.y = player_pos.y - dist.y;
}

int	get_color(char **map, t_double_pos dpos)
{
	t_int_pos	pos;
	
	pos.x = dpos.x;
	pos.y = dpos.y;
	if (is_wall(map, pos))
		return (GREEN);
	return (WHITE);
}

void	save_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &(img->bpp), &(img->size), &(img->endian));
}

double	deg_to_rad(double degree)
{
	return (degree * (M_PI / 180.0));
}