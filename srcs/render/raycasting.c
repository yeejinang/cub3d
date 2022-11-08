/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/11/08 13:55:12 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"

void	init_raycast(t_game *game, t_raycast *rc, int x)
{
	rc->angle = (double)(game->player_pos.angle + (FOV / 2)) - \
				((double)x * (FOV / WIN_WIDTH));
	better_angle(&(rc->angle));
	rc->rayDir.x = cos(deg_to_rad(rc->angle));
	rc->rayDir.y = sin(deg_to_rad(rc->angle));
	rc->map_pos.x = (int)game->player_pos.pos.x0;
	rc->map_pos.y = (int)game->player_pos.pos.y0;
	rc->ray_deduct.x = 0;
	rc->ray_deduct.y = 0;
	rc->deltaDist.x = sqrt(1 + (rc->rayDir.y * rc->rayDir.y) / \
		(rc->rayDir.x * rc->rayDir.x));
	if (fabs(rc->rayDir.x) <= 0.00001)
		rc->deltaDist.x = 1e30;
	rc->deltaDist.y = sqrt(1 + (rc->rayDir.x * rc->rayDir.x) / \
		(rc->rayDir.y * rc->rayDir.y));
	if (fabs(rc->rayDir.y) <= 0.00001)
		rc->deltaDist.y = 1e30;
}

void	set_side_dist(t_game *game, t_raycast *rc)
{
	if (rc->rayDir.x < 0)
	{
		rc->step.x = -1;
		rc->sideDist.x = (game->player_pos.pos.x0 - rc->map_pos.x) * \
			rc->deltaDist.x;
		rc->ray_deduct.x = 1;
	}
	else
	{
		rc->step.x = 1;
		rc->sideDist.x = (rc->map_pos.x + 1.0 - game->player_pos.pos.x0) * \
			rc->deltaDist.x;
	}
	if (rc->rayDir.y < 0)
	{
		rc->step.y = 1;
		rc->sideDist.y = (rc->map_pos.y + 1.0 - game->player_pos.pos.y0) * \
			rc->deltaDist.y;
	}
	else
	{
		rc->step.y = -1;
		rc->sideDist.y = (game->player_pos.pos.y0 - rc->map_pos.y) * \
			rc->deltaDist.y;
		rc->ray_deduct.y = 1;
	}
}

void	determine_hit(t_game *game, t_raycast *rc)
{
	int	hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->map_pos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->map_pos.y += rc->step.y;
			rc->side = 1;
		}
		if ((game->map)[rc->map_pos.y][rc->map_pos.x] == '1')
			hit = 1;
	}
}

void	draw_rays(t_game *game, t_raycast *rc)
{
	t_matrix	draw_ray;

	draw_ray.x0 = game->player_pos.pos.x0;
	draw_ray.y0 = game->player_pos.pos.y0;
	if (rc->side == 0)
	{
		draw_ray.x1 = draw_ray.x0 + (rc->rayDir.x * \
			fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) * \
			rc->deltaDist.x);
		draw_ray.y1 = draw_ray.y0 - (rc->rayDir.y * \
			fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) * \
			rc->deltaDist.x);
	}
	else
	{
		draw_ray.x1 = draw_ray.x0 + (rc->rayDir.x * \
			fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) * \
			rc->deltaDist.y);
		draw_ray.y1 = draw_ray.y0 - (rc->rayDir.y * \
			fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) * \
			rc->deltaDist.y);
	}
	dda_line(draw_ray, game);
}

void	draw_3D(t_game *game)
{
	int			x;
	t_raycast	rc;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_raycast(game, &rc, x);
		set_side_dist(game, &rc);
		determine_hit(game, &rc);
		draw_rays(game, &rc);
		draw_texture(game, &rc, x);
	}
}
