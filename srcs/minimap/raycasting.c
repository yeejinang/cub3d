/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/10/30 22:43:29 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "minimap.h"

#define FOV 66.0
#define STRIPE 800.0
#define h 500
#define MAP_WIDTH 20.0
#define MAP_HEIGHT 15.0

char *map_1[15] = {
	"111111111111111", // 0
	"100000000000001", // 1
	"101000000000001", // 2
	"101000000000001", // 3
	"100000000011101", // 4
	"101000000000010", // 5
	"101000000000001", // 6
	"100001000000001", // 7
	"111111000W00001", // 8
	"100100000001111", // 9
	"100010000000001", // 10
	"100100000000001", // 11
	"100000000000001", // 12
	"100000000000001", // 13
	"111111111111111", // 14
};

void dda(t_matrix matrix, t_minimap *minimap, int color);
double get_max(double x_step, double y_step);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);

void dda_ver(t_matrix matrix, t_minimap *minimap, int color)
{
	int y = (int)matrix.y0;
	while (y < (int)matrix.y1)
	{
		my_mlx_pixel_put(&minimap->map_3d, (int)matrix.x0, y, color);
		y++;
	}
}

void draw_3D(t_game *game, t_minimap *minimap)
{
	int x = -1;

	while (++x < STRIPE)
	{
		double angle;
		angle = (double)(minimap->player_angle + (FOV / 2)) - ((double)x * (FOV / STRIPE));
		printf("angle: %f\n", angle);
		double rayDirX = cos(deg_to_rad(angle));
		double rayDirY = sin(deg_to_rad(angle));
		printf("\nrayDirX: %f\t rayDirY: %f\n", rayDirX, rayDirY);
		t_matrix draw_ray;
		draw_ray.x0 = minimap->player_pos.x0;
		draw_ray.y0 = minimap->player_pos.y0;
		draw_ray.x1 = draw_ray.x0 + ((rayDirX)*5);
		draw_ray.y1 = draw_ray.y0 - ((rayDirY)*5);
		// dda(draw_ray, minimap, 0xFF0000);
		int mapX = (int)minimap->player_pos.x0;
		int mapY = (int)minimap->player_pos.y0;
		// printf("mapX: %d\t mapY: %d\n", mapX, mapY);
		// printf("mapX: %d\t mapY: %d\n", mapX, mapY);
		double sideDistX;
		double sideDistY;
		// double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		// double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double deltaDistX = (rayDirX == 0) ? 1e30 : sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = (rayDirY == 0) ? 1e30 : sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		printf("deltaDistX: %f\t deltaDistY: %f\n", deltaDistX, deltaDistY);
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
			stepY = 1;
			sideDistY = (mapY + 1.0 - minimap->player_pos.y0) * deltaDistY;
		}
		else
		{
			stepY = -1;
			sideDistY = (minimap->player_pos.y0 - mapY) * deltaDistY;
		}
		// if (sideDistX == 0)
		// 	sideDistX += deltaDistX;
		// if (sideDistY == 0)
		// 	sideDistY += deltaDistY;
		printf("sideDistX: %f\t sideDistY: %f\n", sideDistX, sideDistY);
		while (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY <= MAP_HEIGHT && hit == 0)
		{
			// printf("mapX: %d\t mapY: %d\n", mapX, mapY);
			// jump to next map square, either in x-direction, or in y-direction
			// printf("****checking map****\n");
			// printf("sideDistX: %f\t sideDistY: %f\n", sideDistX, sideDistY);
			// if (sideDistX == 0.0 && sideDistY == 0.0)
			// {
			// 	printf("enter here\n");
			// 	sideDistX = deltaDistX;
			// 	sideDistY = deltaDistY;
			// }
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
			printf("map: %c\t x: %d\t y: %d\n", map_1[mapY][mapX], mapX, mapY);
			if (map_1[mapY][mapX] == '1')
			{
				hit = 1;
				double dist;
				t_matrix draw_ray;
				draw_ray.x0 = minimap->player_pos.x0;
				draw_ray.y0 = minimap->player_pos.y0;
				// if (side == 1)
				// 	dist = fabs(mapX - draw_ray.x0 + 1) * deltaDistX;
				// else
				// 	dist = fabs(mapY - draw_ray.y0 + 1) * deltaDistY;
				if (side == 0)
				{
					draw_ray.x1 = draw_ray.x0 + (rayDirX * fabs(mapX - draw_ray.x0 + 1) * deltaDistX);
					draw_ray.y1 = draw_ray.y0 - (rayDirY * fabs(mapX - draw_ray.x0 + 1) * deltaDistX);
				}
				else
				{
					draw_ray.x1 = draw_ray.x0 + (rayDirX * fabs(mapY - draw_ray.y0) * deltaDistY);
					draw_ray.y1 = draw_ray.y0 - (rayDirY * fabs(mapY - draw_ray.y0) * deltaDistY);
				}
				dda(draw_ray, minimap, 0x00FF00);
				printf("x: %d\t hit!!\n", x);
				printf("is side: %d\n", side);
				printf("mapX: %d\t mapY: %d\n", mapX, mapY);
			}
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(h / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		printf("perpWallDist: %f\t lineHeight: %d\n", perpWallDist, lineHeight);
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		printf("drawStart: %d\t drawEnd: %d\n", drawStart, drawEnd);
		int color = 0x0000FF;
		if (side == 1)
		{
			color /= 2;
		}
		t_matrix draw;
		draw.x0 = x * (800 / STRIPE);
		draw.x1 = draw.x0;
		draw.y0 = drawStart;
		draw.y1 = drawEnd;
		dda_ver(draw, minimap, color);
	}
	// my_mlx_pixel_put(&minimap->map_3d, 100, 100, 0xFFFFFF);
	mlx_put_image_to_window(game->mlx, game->win, minimap->map_3d.img, 200, 200);
}
