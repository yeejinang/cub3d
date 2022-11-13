/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:27:17 by yang              #+#    #+#             */
/*   Updated: 2022/11/13 14:25:35 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_raycast(t_game *game, t_raycast *rc);
void set_side_dist(t_game *game, t_raycast *rc);
int determine_hit(t_game *game, t_raycast *rc, bool close_door);
void draw_rays(t_game *game, t_raycast *rc);

// R = (colorINT / 65536); G = (colorINT / 256) % 256; B = colorINT % 256
t_img copy_image(t_game *game, t_img img)
{
	t_img new;
	t_int_pos pos;
	uint32_t color;

	new.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(new));
	pos.y = -1;
	while (++pos.y < WIN_HEIGHT)
	{
		pos.x = -1;
		while (++pos.x < WIN_WIDTH)
		{
			color = get_tex_color(&img, pos.x, pos.y);
			my_mlx_pixel_put(&(new), pos.x, pos.y, color);
		}
	}
	return (new);
}

t_color int_to_rgb(int color)
{
	t_color rgb;

	rgb.r = color / 65536;
	rgb.g = (color / 256) % 256;
	rgb.b = color % 256;
	return (rgb);
}

uint32_t rgb_to_int(t_color rgb)
{
	uint32_t color;

	color = rgb.r;
	color = (color << 8) + rgb.g;
	color = (color << 8) + rgb.b;
	return (color);
}

int get_img_transparent(t_color *first, t_color *second, double percent)
{
	t_color new;

	new.r = (second->r * percent) + (first->r * (1.0 - percent));
	new.g = (second->g * percent) + (first->g * (1.0 - percent));
	new.b = (second->b * percent) + (first->b * (1.0 - percent));
	return (rgb_to_int(new));
}

int is_player_facing_door(t_game *game, t_raycast *rc)
{
	double dist;
	t_matrix *draw_ray;
	int elem;

	draw_ray = &rc->draw_ray;
	init_raycast(game, rc);
	set_side_dist(game, rc);
	elem = determine_hit(game, rc, true);
	if (elem == 2 || elem == 3)
	{
		draw_rays(game, rc);
		dist = sqrt((fabs(ft_sqr(draw_ray->x1 - draw_ray->x0)) + fabs(ft_sqr(draw_ray->y1 - draw_ray->y0))));
		if (dist <= 3.0)
			return (1);
	}
	return (0);
}

void dda_door_3D(t_game *game, t_raycast *rc, int x, double percent)
{
	t_color bg_color;
	t_color door_color;
	uint32_t color;
	int y;

	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		bg_color = int_to_rgb(get_tex_color(&(game->frame_door_open), x, y));
		door_color = int_to_rgb(get_tex_color(&(game->frame_door_close), x, y));
		color = get_img_transparent(&door_color, &bg_color, percent);
		my_mlx_pixel_put(&(game->img_3d), x, y, color);
		y++;
	}
}

void reset_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->minimap.img.img);
	mlx_destroy_image(game->mlx, game->img_3d.img);
	game->minimap.img.img = mlx_new_image(game->mlx, game->minimap.pxsize.x,
										  game->minimap.pxsize.y);
	save_img_addr(&(game->minimap.img));
	game->img_3d.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->img_3d));
	draw_floor_n_ceiling(&(game->img_3d), game->c_color, 0, WIN_HEIGHT / 2);
	draw_floor_n_ceiling(&(game->img_3d), game->f_color,
						 WIN_HEIGHT / 2, WIN_HEIGHT);
}

void frame_door_open_close(t_game *game)
{
	int x;
	t_raycast rc;
	int elem;

	x = -1;
	draw_3D(game);
	game->frame_door_close = copy_image(game, game->img_3d);
	reset_img(game);
	while (++x < WIN_WIDTH)
	{
		rc.angle = (double)(game->player_pos.angle + (FOV / 2)) -
				   ((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc.angle));
		init_raycast(game, &rc);
		set_side_dist(game, &rc);
		elem = determine_hit(game, &rc, true);
		if (elem == 2)
			elem = determine_hit(game, &rc, false);
		draw_rays(game, &rc);
		draw_texture(game, &rc, elem);
		dda_3D(game, &rc, x);
	}
	// for closing door, frame_door_open should be frame with door closing
	game->frame_door_open = copy_image(game, game->img_3d);
}

void frame_door_open_close_2(t_game *game)
{
	int x;
	t_raycast rc;
	int elem;

	x = -1;
	draw_3D(game);
	game->frame_door_open = copy_image(game, game->img_3d);
	reset_img(game);
	while (++x < WIN_WIDTH)
	{
		rc.angle = (double)(game->player_pos.angle + (FOV / 2)) -
				   ((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc.angle));
		init_raycast(game, &rc);
		set_side_dist(game, &rc);
		elem = determine_hit(game, &rc, true);
		draw_rays(game, &rc);
		draw_texture(game, &rc, elem);
		dda_3D(game, &rc, x);
	}
	// for closing door, frame_door_open should be frame with door closing
	game->frame_door_close = copy_image(game, game->img_3d);
}

void single_door_frame(t_game *game, double percent)
{
	t_raycast rc_door;
	int x;
	int elem;

	// frame_door_open_close(game);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		rc_door.angle = (double)(game->player_pos.angle + (FOV / 2)) -
						((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc_door.angle));
		init_raycast(game, &rc_door);
		set_side_dist(game, &rc_door);
		elem = determine_hit(game, &rc_door, false);
		draw_rays(game, &rc_door);
		draw_texture(game, &rc_door, elem);
		if (elem == 2)
			dda_door_3D(game, &rc_door, x, percent);
		else
			dda_3D(game, &rc_door, x);
	}
}

void opening_door(t_game *game, t_raycast *rc)
{
	static double frame = 0.1;

	frame_door_open_close(game);
	if (frame < 1.0)
		single_door_frame(game, frame);
	frame += 0.1;
	printf("frame: %f\n", frame);
	if (frame > 1.000000)
	{
		printf("door opened!\n");
		game->door_status = DOOR_OPENED;
		game->map[rc->map_pos.y][rc->map_pos.x] = '3';
		frame = 0.1;
	}
}

void closing_door(t_game *game, t_raycast *rc)
{
	static double close_frame = 1.0;

	(void)rc;
	frame_door_open_close_2(game);
	// if (!close_frame)
	single_door_frame(game, close_frame);
	// close_frame -= 0.1;
	// printf("frame: %f\n", close_frame);
	// if (close_frame < 0.000000)
	// {
	// 	printf("door closed!\n");
	// 	game->door_status = DOOR_CLOSED;
	// 	game->map[rc->map_pos.y][rc->map_pos.x] = '2';
	// 	close_frame = 1.0;
	// }
}

void handle_door(t_game *game)
{
	t_raycast rc;
	// t_raycast rc_door;
	int x;
	// int elem;

	x = -1;
	rc.angle = game->player_pos.angle;
	printf("handling door\n");
	printf("door status: %d\n", game->door_status);
	// game->door_status = DOOR_CLOSE;
	if (is_player_facing_door(game, &rc))
	{
		// game->prev_frame = game->img_3d;
		// mlx_put_image_to_window(game->mlx, game->win, game->img_3d.img, 0, 0);
		if (game->door_status == DOOR_OPEN)
		{
			printf("opening door...\n");
			game->door_status = DOOR_OPENING;
			printf("door status: %d\n", game->door_status);
		}
		else if (game->door_status == DOOR_CLOSE)
		{
			printf("close door...\n");
			game->door_status = DOOR_CLOSING;
		}
		if (game->door_status == DOOR_OPENING)
		{
			printf("disappering..\n");
			opening_door(game, &rc);
		}
		else if (game->door_status == DOOR_CLOSING)
		{
			printf("closing door..\n");
			closing_door(game, &rc);
		}
	}
	else
		game->door_status = DOOR_CLOSED;
}