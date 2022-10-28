/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:43:44 by yang              #+#    #+#             */
/*   Updated: 2022/10/29 00:56:57 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <mlx.h>
#include "example.h"

#define mapWidth 24
#define mapHeight 24
#define WidthScreen 512
#define HeightScreen 384

void put_color_to_pixel(t_win *win, int x, int y)
{
	int pixel;

	pixel = (x + y * WidthScreen) * 4;
	win->line[pixel + 0] = (unsigned char)((win->color >> 16) & 0xFF);
	win->line[pixel + 1] = (unsigned char)((win->color >> 8) & 0xFF);
	win->line[pixel + 2] = (unsigned char)(win->color & 0xFF);
}

void verLine(int x, int drawStart, int drawEnd, t_win *win)
{
	while (drawStart < drawEnd)
	{
		put_color_to_pixel(win, x, drawStart);
		drawStart++;
	}
}

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void create_image(t_win *win)
{
	// int a[3];

	win->img = mlx_new_image(win->mlx, WidthScreen, HeightScreen);
	win->img->addr = mlx_get_data_addr(win->img, &win->img->bpp, &win->img->size,
									   &win->img->endian);
	;
}

void draw(t_win *win)
{
	double posX = 22, posY = 12;	  // x and y start position
	double dirX = -1, dirY = 0;		  // initial direction vector
	double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

	// clock_t start = 0;
	// clock_t end;
	// double time = 0;	// time of current frame
	// double oldTime = 0; // time of previous frame

	// mlx_clear_window(win->mlx, win->win);
	create_image(win);
	for (int x = 0; x < WidthScreen; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)WidthScreen - 1; // x-coordinate in camera space
		double rayPosX = posX;
		double rayPosY = posY;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		// which box of the map we're in
		int mapX = (int)rayPosX;
		int mapY = (int)rayPosY;

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0;  // was there a wall hit?
		int side = 0; // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
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
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

		// Calculate height of line to draw on screen
		int lineHeight = (int)(HeightScreen / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HeightScreen / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HeightScreen / 2;
		if (drawEnd >= HeightScreen)
			drawEnd = HeightScreen - 1;

		// choose wall color
		// unsigned int color = 0xFFFFFF;
		switch (worldMap[mapX][mapY])
		{
		case 1:
			win->color = 0x00FFFF;
			break; // red
		case 2:
			win->color = 0x0000FF;
			break; // green
		case 3:
			win->color = 0xFF0000;
			break; // blue
		case 4:
			win->color = 0xFFFF00;
			break; // white
		default:
			win->color = 0xFFFFFF;
			break; // yellow
		}

		// give x and y sides different brightness
		if (side == 1)
		{
			win->color = win->color / 2;
		}
		// draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, win);
	}
	// timing for input and FPS counter
	//		oldTime = time;
	//		time = get;
	// end = start;
	// start = clock();
	// double frameTime = (start - end) / CLOCKS_PER_SEC; // frameTime is the time this frame has taken, in seconds
	//	print(1.0 / frameTime); //FPS counter
	//	redraw();
	//	cls();

	// speed modifiers
	// double moveSpeed = frameTime * 5.0; // the constant value is in squares/second
	// double rotSpeed = frameTime * 3.0;	// the constant value is in radians/second
	// readKeys();
	// move forward if no wall in front of you
	//	if (keyDown(SDLK_UP))
	//	{
	//		if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
	//			posX += dirX * moveSpeed;
	//		if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)
	//			posY += dirY * moveSpeed;
	//	}
	//	//move backwards if no wall behind you
	//	if (keyDown(SDLK_DOWN))
	//	{
	//		if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
	//			posX -= dirX * moveSpeed;
	//		if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
	//			posY -= dirY * moveSpeed;
	//	}
	//	//rotate to the right
	//	if (keyDown(SDLK_RIGHT))
	//	{
	//		//both camera direction and camera plane must be rotated
	//		double oldDirX = dirX;
	//		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	//		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	//		double oldPlaneX = planeX;
	//		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	//		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	//	}
	//	//rotate to the left
	//	if (keyDown(SDLK_LEFT))
	//	{
	//		//both camera direction and camera plane must be rotated
	//		double oldDirX = dirX;
	//		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	//		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	//		double oldPlaneX = planeX;
	//		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	//		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	//	}
	mlx_destroy_image(win->mlx, win->img);
}

void write_to_image(t_win *win)
{
	// mlx_clear_window(win->mlx, win->win);
	create_image(win);

	draw(win);

	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	// mlx_hook(win->win, 2, 5, my_key_funct, mod);
	mlx_loop(win->mlx);
}

int main(int argc, char *argv[])
{
	t_win *win = (t_win *)malloc(sizeof(t_win));

	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WidthScreen, HeightScreen, "Wolf3D");
	int a[3];

	if (argc == 1)
	{
		write_to_image(win);
	}
}