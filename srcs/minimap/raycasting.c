/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/11/10 12:17:49 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "minimap.h"

#define FOV 66.0
#define STRIPE 1000.0
#define h 1000
#define MAP_WIDTH 15.0
#define MAP_HEIGHT 15.0
#define TEXSIZE 64

char *map_1[15] = {
	"111111111111111", // 0
	"100000000000001", // 1
	"100000000000001", // 2
	"100000000000001", // 3
	"100000000000001", // 4
	"100000W00000001", // 5
	"100000000000001", // 6
	"100001000000001", // 7
	"100000000W00001", // 8 (8,9)
	"100000000000001", // 9
	"100000000000001", // 10
	"100000000000001", // 11
	"100000000000001", // 12
	"100000000000001", // 13
	"111111111111111", // 14
};

void dda(t_matrix matrix, t_minimap *minimap, int color);
double get_max(double x_step, double y_step);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);

uint32_t	get_tex_color(t_img *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	return (*(uint32_t *)dst);
}

void dda_ver(t_matrix matrix, t_minimap *minimap, t_texture texture)
{
	int y = (int)matrix.y0;
	uint32_t	color;
	while (y < (int)matrix.y1)
	{
		texture.tex_pos.y = (int)texture.tex_start & (TEXSIZE - 1);
		texture.tex_start += texture.step;
		color = get_tex_color(&(texture.img), texture.tex_pos.x, texture.tex_pos.y);
		my_mlx_pixel_put(&minimap->map_3d, (int)matrix.x0, y, color);
		y++;
	}
}

void draw_3D(t_game *game, t_minimap *minimap)
{
	int x = -1;
	t_matrix draw_ray;
	while (++x < STRIPE)
	{
		double angle;
		angle = (double)(minimap->player_angle + (FOV / 2)) - ((double)x * (FOV / STRIPE));
		if (angle < 0.0)
			angle += 360.0;
		else if (angle > 360.0)
			angle -= 360.0;
		double rayDirX = cos(deg_to_rad(angle));
		double rayDirY = sin(deg_to_rad(angle));
		int mapX = (int)minimap->player_pos.x0; // need to know the exact player pos (0.x? and facing direction to get exact starting point)
		int mapY = (int)minimap->player_pos.y0;
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = (rayDirY == 0) ? 1e30 : sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0;
		int side;
		int ray_deduct_x = 0;
		int ray_deduct_y = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (minimap->player_pos.x0 - mapX) * deltaDistX;
			ray_deduct_x = 1;
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
			ray_deduct_y = 1;
		}
		while (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY <= MAP_HEIGHT && hit == 0)
		{
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
			if (map_1[mapY][mapX] == '1')
			{
				hit = 1;
				draw_ray.x0 = minimap->player_pos.x0;
				draw_ray.y0 = minimap->player_pos.y0;
				if (side == 0)
				{
					draw_ray.x1 = draw_ray.x0 + (rayDirX * fabs(mapX - draw_ray.x0 + ray_deduct_x) * deltaDistX);
					draw_ray.y1 = draw_ray.y0 - (rayDirY * fabs(mapX - draw_ray.x0 + ray_deduct_x) * deltaDistX);
				}
				else
				{
					draw_ray.x1 = draw_ray.x0 + (rayDirX * fabs(mapY - draw_ray.y0 + ray_deduct_y) * deltaDistY);
					draw_ray.y1 = draw_ray.y0 - (rayDirY * fabs(mapY - draw_ray.y0 + ray_deduct_y) * deltaDistY);
				}
				dda(draw_ray, minimap, 0x00FF00);
			}
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		double ca = minimap->player_angle - angle;
		if (ca < 0.0)
			ca += 360.0;
		else if (ca >= 360.0)
			ca -= 360.0;
		int lineHeight = (int)(h / (perpWallDist * cos(deg_to_rad(ca))));

		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		int color = 0x0000FF;
		if (side == 1)
			color /= 2;
		
		
		t_texture	texture;
		texture.step = 1.0 * TEXSIZE / lineHeight;
		double wallX;
		
    //  double cameraX = 2*x/(double)1000-1; //x-coordinate in camera space
		//   rayDirX = minimap->player_pos.x1 + cameraX;
		//   rayDirY = minimap->player_pos.y1 + cameraX;
		if (side == 0)
			wallX = draw_ray.y1;
		else
			wallX = draw_ray.x1;
		// if (side == 0)  //if side == 0, hit y-axis (West or East)
		// 	wallX = minimap->player_pos.y0 + perpWallDist * rayDirY;
		// else wallX = minimap->player_pos.x0 + perpWallDist * rayDirX;
		printf("wallX: %f\n", wallX);
		wallX -= (int)wallX;
		texture.tex_pos.x = (int)(wallX * (double)TEXSIZE);
		if (side == 0 && rayDirX > 0.0) 
		{
			texture.tex_pos.x = TEXSIZE - texture.tex_pos.x - 1;
		}
		if (side == 1 && rayDirY < 0.0) 
			texture.tex_pos.x = TEXSIZE - texture.tex_pos.x - 1;
		texture.tex_start = (drawStart - h / 2 + lineHeight / 2) * texture.step;
		texture.img = game->wall_EA;
		t_matrix draw;
		draw.x0 = x;
		draw.y0 = drawStart;
		draw.y1 = drawEnd;
		if (side == 0)
			dda_ver(draw, minimap, texture);
	}
	mlx_put_image_to_window(game->mlx, game->win, minimap->map_3d.img, 0, 0);
}


