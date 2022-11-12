/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:27:17 by yang              #+#    #+#             */
/*   Updated: 2022/11/10 16:54:02 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_raycast(t_game *game, t_raycast *rc);
void	set_side_dist(t_game *game, t_raycast *rc);
int	determine_hit(t_game *game, t_raycast *rc);
void	draw_rays(t_game *game, t_raycast *rc);

// R = (colorINT / 65536); G = (colorINT / 256) % 256; B = colorINT % 256
t_img    copy_image(t_game *game, t_img img)
{
    t_img        new;
    t_int_pos    pos;
    uint32_t    color;

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

uint32_t	rgb_to_int(t_color rgb)
{
	uint32_t	color;

	color = rgb.r;
	color = (color << 8) + rgb.g;
	color = (color << 8) + rgb.b;
	return (color);
}
// Rnew = (Rtop * alpha) + (Rbottom * (1.0 - alpha))
// Gnew = (Gtop * alpha) + (Gbottom * (1.0 - alpha))
// Bnew = (Btop * alpha) + (Bbottom * (1.0 - alpha))
int get_img_transparent(t_color *first, t_color *second, double percent)
{
	t_color new;

	new.r = (first->r * percent) + (second->r * (1.0 - percent));
	new.g = (first->g * percent) + (second->g * (1.0 - percent));
	new.b = (first->b * percent) + (second->b * (1.0 - percent));
	return (rgb_to_int(new));
}

int	is_player_facing_door(t_game *game, t_raycast *rc)
{
	double dist;
	t_matrix *draw_ray = &rc->draw_ray;

	init_raycast(game, rc);
	set_side_dist(game, rc);
	if (determine_hit(game, rc) == 2)
	{
		draw_rays(game, rc);
		dist = sqrt((fabs(ft_sqr(draw_ray->x1 - draw_ray->x0)) \
				+ fabs(ft_sqr(draw_ray->y1 - draw_ray->y0))));
		// printf("dist: %f\n", dist);
		if (dist <= 3.0)
			return (1);
	}
	return (0);
}

void	dda_door_3D(t_game *game, t_raycast *rc, int x, double percent)
{
	t_color	bg_color;
	t_color	door_color;
	uint32_t	color;
	// t_matrix 	draw;
	int y;
	
	y = rc->draw_start;
	// printf("y: %d\n", y);
	while (y < rc->draw_end)
	{
		// rc->texture.tex_pos.y = (int)rc->texture.tex_start & (TEXSIZE - 1);
		// rc->texture.tex_start += rc->texture.step;
		// printf("tex_pos_y: %d\t tex_start: %d\n", rc->texture.tex_pos.y, rc->texture.tex_start);
		// bg_color = int_to_rgb(get_tex_color(&(rc->texture.img), rc->texture.tex_pos.x, \
		// 						rc->texture.tex_pos.y));
		bg_color = int_to_rgb(get_tex_color(&(game->frame_door_open), x, y));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 3, 2, rgb_to_int(bg_color));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 3, 3, rgb_to_int(bg_color));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 3, 4, rgb_to_int(bg_color));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 3, 5, rgb_to_int(bg_color));
		// printf("x: %d\t y: %d\n", x, y);
		//door color incorrect, this only get background color
		door_color = int_to_rgb(get_tex_color(&(game->frame_door_close), x, y));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 1, 2, rgb_to_int(door_color));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 1, 3, rgb_to_int(door_color));	
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 1, 4, rgb_to_int(door_color));
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 1, 5, rgb_to_int(door_color));
		color = get_img_transparent(&door_color, &bg_color, percent);
		// my_mlx_pixel_put(&(game->img_3d), WIN_WIDTH - 1, 2, color);
		// printf("color: %d\n", color);
		my_mlx_pixel_put(&(game->img_3d), x, y, color);
		y++;
	}
}

void reset_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->minimap.img.img);
	mlx_destroy_image(game->mlx, game->img_3d.img);
	game->minimap.img.img = mlx_new_image(game->mlx, game->minimap.pxsize.x, \
											game->minimap.pxsize.y);
	save_img_addr(&(game->minimap.img));
	game->img_3d.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->img_3d));
	draw_floor_n_ceiling(&(game->img_3d), game->c_color, 0, WIN_HEIGHT / 2);
	draw_floor_n_ceiling(&(game->img_3d), game->f_color, \
							WIN_HEIGHT / 2, WIN_HEIGHT);
}

void single_door_frame(t_game *game, double percent)
{
	t_raycast	rc;
	t_raycast	rc_door;
	int			x;
	int			elem;

	x = -1;
	draw_3D(game);
	game->frame_door_close = copy_image(game, game->img_3d);
	reset_img(game);
	while (++x < WIN_WIDTH)
	{
		rc.angle = (double)(game->player_pos.angle + (FOV / 2)) - \
				((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc.angle));
		init_raycast(game, &rc);
		set_side_dist(game, &rc);
		elem = determine_hit(game, &rc);
		if (elem == 2)
		{
			draw_rays(game, &rc);
			draw_texture(game, &rc, elem);
			dda_3D(game, &rc, x);
			// game->map[rc.map_pos.y][rc.map_pos.x] = '3';
			
		}
		else
		{
			draw_rays(game, &rc);
			draw_texture(game, &rc, elem);
			dda_3D(game, &rc, x);
		}
	}
	game->frame_door_open = copy_image(game, game->img_3d);
	// mlx_destroy_image(game->mlx, game->img_3d.img);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		rc_door.angle = (double)(game->player_pos.angle + (FOV / 2)) - \
				((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc_door.angle));
		init_raycast(game, &rc_door);
		set_side_dist(game, &rc_door);
		elem = determine_hit(game, &rc_door);
		draw_rays(game, &rc_door);
		printf("draw start: %d\n", rc_door.draw_start);
		draw_texture(game, &rc_door, elem);
		if (elem == 2)
			dda_door_3D(game, &rc_door, x, percent);
			// game->map[rc.map_pos.y][rc.map_pos.x] = '3';
		else
			dda_3D(game, &rc_door, x);
	}
}

void opening_door(t_game *game)
{
	double percent = 0.1;

	while (percent <= 1.0)
	{
		single_door_frame(game, percent);
		
		percent += 0.1;
	}
	game->door_status = OPENED;
}

void handle_door(t_game *game)
{
	t_raycast	rc;
	t_raycast	rc_door;
	int			x;
	int			elem;

	x = -1;
	rc.angle = game->player_pos.angle;
	printf("handling door\n");
	if (is_player_facing_door(game, &rc) || game->door_status == OPENING)
	{
		// game->prev_frame = game->img_3d;
		// mlx_put_image_to_window(game->mlx, game->win, game->img_3d.img, 0, 0);
		if(game->door_status == OPEN)
			game->door_status = OPENING;
		else if (game->door_status == CLOSE)
			game->door_status = CLOSING;
		draw_3D(game);
		game->frame_door_close = copy_image(game, game->img_3d);
		reset_img(game);
		// opening_door(game);
		while (++x < WIN_WIDTH)
		{
			rc.angle = (double)(game->player_pos.angle + (FOV / 2)) - \
					((double)x * (FOV / WIN_WIDTH));
			better_angle(&(rc.angle));
			init_raycast(game, &rc);
			set_side_dist(game, &rc);
			elem = determine_hit(game, &rc);
			if (elem == 2)
			{
				//draw texture combine background behind door + door
				//now at the pixel of door, need to get background
				// game->door_status = OPENING;
				// game->map[rc.map_pos.y][rc.map_pos.x] = '3';
				// draw_rays(game, &rc_door);
				elem = determine_hit(game, &rc); // this able to get background hit position
				draw_rays(game, &rc);
				draw_texture(game, &rc, elem);
				dda_3D(game, &rc, x);
				// game->map[rc.map_pos.y][rc.map_pos.x] = '3';
				
			}
			else
			{
				draw_rays(game, &rc);
				draw_texture(game, &rc, elem);
				dda_3D(game, &rc, x);
			}
		}
		game->frame_door_open = copy_image(game, game->img_3d);
		// mlx_destroy_image(game->mlx, game->img_3d.img);
		x = -1;
		while (++x < WIN_WIDTH)
		{
			rc_door.angle = (double)(game->player_pos.angle + (FOV / 2)) - \
					((double)x * (FOV / WIN_WIDTH));
			better_angle(&(rc_door.angle));
			init_raycast(game, &rc_door);
			set_side_dist(game, &rc_door);
			elem = determine_hit(game, &rc_door);
			draw_rays(game, &rc_door);
			printf("draw start: %d\n", rc_door.draw_start);
			draw_texture(game, &rc_door, elem);
			if (elem == 2)
				dda_door_3D(game, &rc_door, x, 0.5);
				// game->map[rc.map_pos.y][rc.map_pos.x] = '3';
			else
				dda_3D(game, &rc_door, x);
		}
	}
	// draw_3D(game);
}