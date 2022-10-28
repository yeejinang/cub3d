/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/10/29 01:49:16 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "minimap.h"

#define FOV 66
#define STRIPE 10
#define h 1000
#define MAP_WIDTH 20.0
#define MAP_HEIGHT 15.0

char *map_1[15] = {
	"11111111111111111111",
	"10000010000000100001",
	"101000100W0000100001",
	"10100010000000100001",
	"10000000001110100001",
	"10000100000001000001",
	"10000100000000100001",
	"10000100000000100001",
	"11111100000000100001",
	"10000000000111100001",
	"10000000000000100001",
	"1000000E000000100001",
	"10000000000000100001",
	"10000000000000100001",
	"11111111111111111111",
};

void dda(t_matrix matrix, t_minimap *minimap, int color);
double get_max(double x_step, double y_step);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);

void dda_ver(t_matrix matrix, t_minimap *minimap, int color)
{
	// printf("drawing ....\n");
	// printf("matrix x0: %f\t x1: %f\t y0: %f\t y1: %f\n", matrix.x0, matrix.x1, matrix.y0, matrix.y1);
	// double x_step;
	// double y_step;
	// double max;

	// x_step = matrix.x1 - matrix.x0;
	// y_step = matrix.y1 - matrix.y0;
	// max = get_max(x_step, y_step);
	// x_step /= max;
	// y_step /= max;
	// int x = (int)matrix.x0;
	int y = (int)matrix.y0;
	// printf("color: %d\n", color);
	// while (x < (int)matrix.x1)
	// {
	y = 0;
	while (y < (int)matrix.y1)
	{
		my_mlx_pixel_put(&minimap->map_3d, (int)matrix.x0, y, color);
		// printf("drawing into img\n");
		y++;
	}
	// 	x++;
	// }
}

void draw_3D(t_game *game, t_minimap *minimap)
{
	int x = -1;
	// double angle;
	// printf("player angle: %f\n", minimap->player_angle);
	// double rayX = cos(deg_to_rad((int)(minimap->player_angle + (FOV / 2) % 360)));
	// double rayY = sin(deg_to_rad((int)(minimap->player_angle + (FOV / 2) % 360)));
	// Assumptions
	// double planeX = 0.0;
	// double planeY = 0.66;
	// printf("planeX: %f\t planeY: %f\n", planeX, planeY);

	while (++x <= STRIPE)
	{
		double angle;
		angle = (int)(minimap->player_angle + (FOV / 2)) % 360 - (x * (FOV / STRIPE));
		// printf("angle: %f\n", angle);
		double rayDirX = cos(deg_to_rad((int)(angle)));
		double rayDirY = sin(deg_to_rad((int)(angle)));
		// t_matrix draw_ray;
		// draw_ray.x0 = minimap->player_pos.x0;
		// draw_ray.y0 = minimap->player_pos.y0;
		// draw_ray.x1 = draw_ray.x0 + (rayDirX);
		// draw_ray.y1 = draw_ray.y0 - (rayDirY);
		// dda(draw_ray, minimap);
		int mapX = (int)minimap->player_pos.x0;
		int mapY = (int)minimap->player_pos.y0;
		// printf("mapX: %d\t mapY: %d\n", mapX, mapY);
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;	 // was a NS o
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (minimap->player_pos.x0 - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - minimap->player_pos.x0) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (minimap->player_pos.y0 - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - minimap->player_pos.y0) * deltaDistY;
		}
		while (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY <= MAP_HEIGHT && hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			// printf("checking hit\n");
			// printf("map: %c\t x: %d\t y: %d\n", map_1[mapX][mapY], mapX, mapY);
			if (map_1[mapX][mapY] == '1')
			{
				hit = 1;
				printf("hit!!\n");
				printf("mapX: %d\t mapY: %d\n", mapX, mapY);
			}
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(h / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		int color = 0x0000FF;
		// if (side == 1)
		// {
		// 	color = 0xFF0000;
		// }

		t_matrix draw;
		draw.x0 = x * (1000 / STRIPE);
		draw.x1 = draw.x0;
		draw.y0 = drawStart;
		draw.y1 = drawEnd;
		dda_ver(draw, minimap, color);
	}
	// my_mlx_pixel_put(&minimap->map_3d, 100, 100, 0xFFFFFF);
	mlx_put_image_to_window(game->mlx, game->win, minimap->map_3d.img, 0, 0);
}
