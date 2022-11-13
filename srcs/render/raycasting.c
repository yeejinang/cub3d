/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/11/13 14:06:50 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_raycast(t_game *game, t_raycast *rc)
{
	// rc->angle = (double)(game->player_pos.angle + (FOV / 2)) - \
	// 			((double)x * (FOV / WIN_WIDTH));
	// better_angle(&(rc->angle));
	rc->rayDir.x = cos(deg_to_rad(rc->angle));
	rc->rayDir.y = sin(deg_to_rad(rc->angle));
	rc->map_pos.x = (int)game->player_pos.pos.x0;
	rc->map_pos.y = (int)game->player_pos.pos.y0;
	rc->ray_deduct.x = 0;
	rc->ray_deduct.y = 0;
	rc->deltaDist.x = sqrt(1 + (rc->rayDir.y * rc->rayDir.y) /
								   (rc->rayDir.x * rc->rayDir.x));
	if (fabs(rc->rayDir.x) <= 0.00001)
		rc->deltaDist.x = 1e30;
	rc->deltaDist.y = sqrt(1 + (rc->rayDir.x * rc->rayDir.x) /
								   (rc->rayDir.y * rc->rayDir.y));
	if (fabs(rc->rayDir.y) <= 0.00001)
		rc->deltaDist.y = 1e30;
}

void set_side_dist(t_game *game, t_raycast *rc)
{
	if (rc->rayDir.x < 0)
	{
		rc->step.x = -1;
		rc->sideDist.x = (game->player_pos.pos.x0 - rc->map_pos.x) *
						 rc->deltaDist.x;
		rc->ray_deduct.x = 1;
	}
	else
	{
		rc->step.x = 1;
		rc->sideDist.x = (rc->map_pos.x + 1.0 - game->player_pos.pos.x0) *
						 rc->deltaDist.x;
	}
	if (rc->rayDir.y < 0)
	{
		rc->step.y = 1;
		rc->sideDist.y = (rc->map_pos.y + 1.0 - game->player_pos.pos.y0) *
						 rc->deltaDist.y;
	}
	else
	{
		rc->step.y = -1;
		rc->sideDist.y = (game->player_pos.pos.y0 - rc->map_pos.y) *
						 rc->deltaDist.y;
		rc->ray_deduct.y = 1;
	}
}

int determine_hit(t_game *game, t_raycast *rc, bool close_door)
{
	int hit;
	int elem;

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
		elem = is_wall_door(game->map, rc->map_pos);
		if (elem == 1 || elem == 2 || (close_door && elem == 3))
			hit = 1;
	}
	return (elem);
}

void draw_rays(t_game *game, t_raycast *rc)
{
	t_matrix draw_ray;

	draw_ray.x0 = game->player_pos.pos.x0;
	draw_ray.y0 = game->player_pos.pos.y0;
	if (rc->side == 0)
	{
		draw_ray.x1 = draw_ray.x0 + (rc->rayDir.x *
									 fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) *
									 rc->deltaDist.x);
		draw_ray.y1 = draw_ray.y0 - (rc->rayDir.y *
									 fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) *
									 rc->deltaDist.x);
	}
	else
	{
		draw_ray.x1 = draw_ray.x0 + (rc->rayDir.x *
									 fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) *
									 rc->deltaDist.y);
		draw_ray.y1 = draw_ray.y0 - (rc->rayDir.y *
									 fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) *
									 rc->deltaDist.y);
	}
	dda_line(draw_ray, game);
	rc->draw_ray = draw_ray;
}

void draw_3D(t_game *game)
{
	int x;
	t_raycast rc;
	int elem;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		rc.angle = (double)(game->player_pos.angle + (FOV / 2)) -
				   ((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc.angle));
		init_raycast(game, &rc);
		set_side_dist(game, &rc);
		elem = determine_hit(game, &rc, false);
		draw_rays(game, &rc);
		draw_texture(game, &rc, elem);
		dda_3D(game, &rc, x);
	}
}
