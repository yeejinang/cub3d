/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:55:27 by hyap              #+#    #+#             */
/*   Updated: 2022/11/08 13:55:32 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	pre_draw_texture(t_game *game, t_raycast *rc)
{
	double	ca;
	
	rc->perpWallDist = (rc->sideDist.y - rc->deltaDist.y);
	if (rc->side == 0)
		rc->perpWallDist = (rc->sideDist.x - rc->deltaDist.x);
	ca = game->player_pos.angle - rc->angle;
	better_angle(&ca);
	rc->line_height = WIN_HEIGHT / (rc->perpWallDist * cos(deg_to_rad(ca)));
	rc->draw_start = -rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_end >= WIN_HEIGHT)
		rc->draw_end = WIN_HEIGHT - 1;
}


void dda_3D(t_game *game, t_raycast *rc, int x)
{
	uint32_t	color;
	int y;
	
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->texture.tex_pos.y = (int)rc->texture.tex_start & (TEXSIZE - 1);
		rc->texture.tex_start += rc->texture.step;
		color = get_tex_color(&(rc->texture.img), rc->texture.tex_pos.x, \
								rc->texture.tex_pos.y);
		my_mlx_pixel_put(&(game->img_3d), x, y, color);
		y++;
	}
}

void	draw_texture(t_game *game, t_raycast *rc, int x)
{
	pre_draw_texture(game, rc);
	rc->texture.step = 1.0 * TEXSIZE / rc->line_height;
	rc->wall.x = game->player_pos.pos.x0 + (rc->perpWallDist * rc->rayDir.x);
	if (rc->side == 0)
	{
		// printf("side: %d\n", rc->side);
		rc->wall.x = game->player_pos.pos.y0 + (rc->perpWallDist * rc->rayDir.y);
	}
	rc->wall.x -= (int)rc->wall.x;
	rc->texture.tex_pos.x = (int)(rc->wall.x * (double)TEXSIZE);
	if (rc->side == 0 && rc->rayDir.x > 0.0) 
		rc->texture.tex_pos.x = TEXSIZE - rc->texture.tex_pos.x - 1;
	if (rc->side == 1 && rc->rayDir.y < 0.0) 
		rc->texture.tex_pos.x = TEXSIZE - rc->texture.tex_pos.x - 1;
	rc->texture.tex_start = rc->texture.step * \
		(rc->draw_start - WIN_HEIGHT / 2 + rc->line_height / 2);
	rc->texture.img = game->wall_EA;
	dda_3D(game, rc, x);
}