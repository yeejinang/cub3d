#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "minimap.h"

#define PLAYER_STEP 0.25
// Player step and player side is the same
// tile : player  = 1.0 : 0.2
#define MINIMAP_WIDTH 10.0 // total tiles
#define MINIMAP_HEIGHT 10.0
#define MI_SCREEN_WIDTH 200
#define MI_SCREEN_HEIGHT 200 // in pixel

// Assumptions
#define MAP_WIDTH 15.0
#define MAP_HEIGHT 15.0

/* display minimap player in center (N, S, E or W)
 ** get map start x and y
 ** start x = player.x - 5
 **			case if player is at the corner
 **			check if (player.x - 5 < 0 || player.x + 5 > map.height)
 **				then start x = 0 || start x = map.height - 10
 */

char *map[15] = {
	"111111111111111",
	"101000000000001",
	"101000000000001",
	"101000000000001",
	"10000000N011101",
	"100001000000010",
	"100001000000001",
	"100001000000001",
	"111111000000001",
	"100000000001111",
	"100000000000001",
	"100000000000001",
	"100000000000001",
	"100000000000001",
	"111111111111111",
};

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void get_start_pt(t_minimap *minimap, double x, double y)
{
	double dis_player_pos = (MINIMAP_WIDTH - PLAYER_STEP) / 2;
	if (x - dis_player_pos < 0.0)
		minimap->start_x = 0.0;
	else if (x + dis_player_pos + PLAYER_STEP > (double)MAP_WIDTH)
		minimap->start_x = (double)MAP_WIDTH - MINIMAP_WIDTH;
	else
		minimap->start_x = x - dis_player_pos;
	if (y - dis_player_pos < 0.0)
		minimap->start_y = 0.0;
	else if (y + dis_player_pos + PLAYER_STEP > (double)MAP_HEIGHT)
		minimap->start_y = (double)MAP_HEIGHT - MINIMAP_HEIGHT;
	else
		minimap->start_y = y - dis_player_pos;
}

void set_player_direction(t_minimap *minimap)
{
	minimap->player_pos.x1 = minimap->player_pos.x0 +
							 cos(deg_to_rad(minimap->player_angle));
	minimap->player_pos.y1 = minimap->player_pos.y0 -
							 sin(deg_to_rad(minimap->player_angle));
}

void set_player_pos(char c, t_int_pos pos, t_minimap *minimap)
{
	if (c == 'E')
		minimap->player_angle = 0;
	else if (c == 'N')
		minimap->player_angle = 90;
	else if (c == 'W')
		minimap->player_angle = 180;
	else
		minimap->player_angle = 270;
	minimap->player_pos.x0 = (double)pos.x;
	minimap->player_pos.y0 = (double)pos.y;
	set_player_direction(minimap);
	// printf("player angle: %f\n", minimap->player_angle);
	printf("player pos x: %f\t y: %f\n", minimap->player_pos.x0, minimap->player_pos.y0);
	// printf("player facing x: %f\t y: %f\n", minimap->player_pos.x1, minimap->player_pos.y1);
}

// find the player position on map, and set player facing direction
void set_player(t_minimap *minimap)
{
	t_int_pos pos;

	pos.y = 0;
	while (pos.y < MAP_HEIGHT)
	{
		pos.x = 0;
		while (pos.x < MAP_WIDTH)
		{
			if (map[pos.y][pos.x] == 'N' || map[pos.y][pos.x] == 'S' || map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'W')
			{
				set_player_pos(map[pos.y][pos.x], pos, minimap);
				break;
			}
			pos.x++;
		}
		pos.y++;
	}
}

// typedef struct s_minimap
// {
// 	double 		start_x;
// 	double 		start_y;
// 	t_matrix	player_pos; // player_pos to facing direction
// 	int			line_len;
// 	double 		scale;
// 	double 		player_delta_x;
// 	double 		player_delta_y;
// 	double 		player_angle; // in degree
// 	t_img 		map;
// 	t_img		floor;
// 	t_img		wall;
// } t_minimap;

void init_minimap(t_minimap *minimap, bool first)
{
	if (first)
		set_player(minimap);
	printf("init map\t player pos x: %f\t y: %f\n", minimap->player_pos.x0, minimap->player_pos.y0);
	get_start_pt(minimap, minimap->player_pos.x0, minimap->player_pos.y0);
	minimap->line_len = 1;
	minimap->scale = MI_SCREEN_WIDTH / MINIMAP_WIDTH;
}

void draw_minimap_block(t_minimap *minimap, int color, t_matrix *pixel, bool isPlayer)
{
	// t_int_pos box_size;
	int draw_size;
	t_int_pos count;

	// box_size.y = minimap->height / 11;
	// box_size.x = minimap->width / 11;
	count.y = 0;
	if (isPlayer)
		printf("drawing player\n");
	while ((pixel->y0 + count.y) < pixel->y1)
	{
		// printf("enter drawing block y\n");
		count.x = 0;
		while ((pixel->x0 + count.x) < pixel->x1)
		{
			// int pixel_x = fabs(pos.x - minimap->start_x) * minimap->scale + count.x;
			// int pixel_y = fabs(pos.y - minimap->start_y) * minimap->scale + count.y;
			if (!isPlayer && (pixel->x0 + count.x) <= 200 && (pixel->y0 + count.y) <= 200)
				my_mlx_pixel_put(&minimap->map, pixel->x0 + count.x, pixel->y0 + count.y, color);
			else
				my_mlx_pixel_put(&minimap->map, (minimap->player_pos.x0 - minimap->start_x) * minimap->scale + count.x,
								 (minimap->player_pos.y0 - minimap->start_y) * minimap->scale + count.y, color);
			count.x++;
		}
		count.y++;
	}
	// printf("end\n");
}

int absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

double get_max(double x_step, double y_step)
{
	if (absolute(x_step) > absolute(y_step))
		return (absolute(x_step));
	else
		return (absolute(y_step));
}

t_matrix scale(t_matrix matrix, t_minimap *minimap)
{
	matrix.x0 = matrix.x0 * minimap->scale;
	matrix.x1 = matrix.x1 * minimap->scale;
	matrix.y0 = matrix.y0 * minimap->scale;
	matrix.y1 = matrix.y1 * minimap->scale;
	return (matrix);
}

t_matrix centralize(t_matrix matrix, t_minimap *minimap)
{
	matrix.x0 -= minimap->start_x;
	matrix.x1 -= minimap->start_x;
	matrix.y0 -= minimap->start_y;
	matrix.y1 -= minimap->start_y;
	return (matrix);
}
void dda(t_matrix matrix, t_minimap *minimap)
{
	double x_step;
	double y_step;
	double max;

	matrix = centralize(matrix, minimap);
	matrix = scale(matrix, minimap);
	x_step = matrix.x1 - matrix.x0;
	y_step = matrix.y1 - matrix.y0;
	max = get_max(x_step, y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(matrix.x0 - matrix.x1) || (int)(matrix.y0 - matrix.y1))
	{
		my_mlx_pixel_put(&minimap->map, matrix.x0, matrix.y0, 0x00FF00);
		matrix.x0 += x_step;
		matrix.y0 += y_step;
	}
}
// draw minimap for 11 * 11 map into 200 * 200 pixel
// void draw_minimap(t_minimap *minimap)
// {
// 	t_int_pos pos;
// 	pos.y = round(minimap->start_y);
// 	int color;

// 	while (pos.y < 11 + minimap->start_y)
// 	{
// 		pos.x = round(minimap->start_x);
// 		while (pos.x < (11 + round(minimap->start_x)))
// 		{
// 			if (map[pos.y][pos.x] == '1')
// 				color = 0x58D68D;
// 			else if (map[pos.y][pos.x] == '0' || (map[pos.y][pos.x] == 'N' || map[pos.y][pos.x] == 'S' || map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'W'))
// 				color = 0xFFFFFF;
// 			else if (map[pos.y][pos.x] == ' ')
// 				color = 0x0000FF;
// 			// else
// 			// 	color = 0xEC7063;
// 			draw_minimap_block(minimap, color, pos, 0);
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// 	// draw player
// 	draw_minimap_block(minimap, 0xEC7063, pos, 1);
// 	// dda(minimap->player_pos, minimap);
// }

// try using
void draw_minimap(t_minimap *minimap)
{
	t_int_pos pos;
	t_matrix pixel;
	pos.y = minimap->start_y;
	int color;

	pixel.y0 = 0;
	int extra_x = 0;
	int extra_y = 0;
	if (minimap->start_x - (int)minimap->start_x)
		extra_x = 1;
	if (minimap->start_y - (int)minimap->start_y)
		extra_y = 1;
	printf("scale: %f\n", minimap->scale);
	while (pos.y < (int)(MINIMAP_HEIGHT + minimap->start_y + extra_y))
	{
		printf("pos.y: %d\t condition: %f\n", pos.y, MINIMAP_HEIGHT + minimap->start_y + extra_y);
		pos.x = minimap->start_x;
		// printf("minimap start x: %f\t y: %f\n", minimap->start_x, minimap->start_y);
		if (pixel.y0 == 0 && (minimap->start_y - (int)minimap->start_y))
			pixel.y1 = ((1.0 - (minimap->start_y - (int)minimap->start_y)) * minimap->scale) - 1;
		else if (pos.y == round(MINIMAP_HEIGHT + minimap->start_y - 1) + extra_y)
		{
			// printf("drawing final pixel\n");
			pixel.y1 = 200;
			printf("drawing final pixel\n");
		}
		else
			pixel.y1 = pixel.y0 + minimap->scale - 1;
		pixel.x0 = 0;
		printf("pixel y0: %f\t y1: %f\t color: %d\n", pixel.y0, pixel.y1, color);
		while (pos.x < MINIMAP_WIDTH + minimap->start_x + extra_x)
		{
			// printf("pos y: %d\t pos: x: %d\n", pos.y, pos.x);
			if (pixel.x0 == 0 && (minimap->start_x - (int)minimap->start_x))
				pixel.x1 = ((1.0 - (minimap->start_x - (int)minimap->start_x)) * minimap->scale) - 1;
			else if (pos.x == round(MINIMAP_WIDTH + minimap->start_x - 1) + extra_x)
			{
				// printf("drawing final pixel\n");
				pixel.x1 = 200;
				// printf("drawing final pixel\n");
			}
			else
				pixel.x1 = pixel.x0 + minimap->scale - 1;
			if (map[pos.y][pos.x] == '1')
				color = 0x58D68D;
			else if (map[pos.y][pos.x] == '0' || (map[pos.y][pos.x] == 'N' || map[pos.y][pos.x] == 'S' || map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'W'))
				color = 0xFFFFFF;
			else if (map[pos.y][pos.x] == ' ')
				color = 0x0000FF;
			// else
			// 	color = 0xEC7063;
			printf("pixel x0: %f\t x1: %f\t color: %d\n", pixel.x0, pixel.x1, color);
			draw_minimap_block(minimap, color, &pixel, 0);
			pixel.x0 = pixel.x1 + 1;
			pos.x++;
		}
		pixel.y0 = pixel.y1 + 1;
		pos.y++;
	}
	// draw player
	t_matrix draw_end_line;
	draw_end_line.x0 = 198;
	draw_end_line.x1 = 200;
	draw_end_line.y0 = 0;
	draw_end_line.y1 = 200;
	draw_minimap_block(minimap, 0xEC7063, &draw_end_line, 0);
	// dda(minimap->player_pos, minimap);
}
// void draw_minimap(t_minimap *minimap)
// {
// }
void display_minimap(t_game *game, t_minimap *minimap)
{
	minimap->map.img = mlx_new_image(game->mlx, MI_SCREEN_WIDTH, MI_SCREEN_HEIGHT);
	minimap->map.addr = mlx_get_data_addr(minimap->map.img, &minimap->map.bpp, &minimap->map.size,
										  &minimap->map.endian);
	draw_minimap(minimap);
	mlx_put_image_to_window(game->mlx, game->win, minimap->map.img, 0, 0);
}

void close_win(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void player_movement(int key, t_game *game)
{
	t_minimap *minimap = game->minimap;
	// printf("key: %d\n", key);
	if (key == 123)
	{
		// 	minimap->player_angle -= 0.1;
		// 	if (minimap->player_angle < 0)
		// 		minimap->player_angle += 2 * PI;
		// 	minimap->player_delta_x = cos(minimap->player_angle) * minimap->line_len;
		// 	minimap->player_delta_y = sin(minimap->player_angle) * minimap->line_len;
		// 	minimap->player_pos.x1 = minimap->player_pos.x0 + minimap->player_delta_x;
		// 	minimap->player_pos.y1 = minimap->player_pos.y0 + minimap->player_delta_y;
		minimap->player_pos.x0 -= PLAYER_STEP;
	}
	else if (key == 124)
	{
		// minimap->player_angle += 0.1;
		// if (minimap->player_angle > 2 * PI)
		// 	minimap->player_angle -= 2 * PI;
		// minimap->player_delta_x = cos(minimap->player_angle) * minimap->line_len;
		// minimap->player_delta_y = sin(minimap->player_angle) * minimap->line_len;
		// minimap->player_pos.x1 = minimap->player_pos.x0 + minimap->player_delta_x;
		// minimap->player_pos.y1 = minimap->player_pos.y0 + minimap->player_delta_y;
		minimap->player_pos.x0 += PLAYER_STEP;
	}
	else if (key == 126)
	{
		// minimap->player_pos.x0 += (minimap->player_delta_x / 5);
		// minimap->player_pos.y0 += (minimap->player_delta_y / 5);
		// minimap->player_pos.x1 += (minimap->player_delta_x / 5);
		// minimap->player_pos.y1 += (minimap->player_delta_y / 5);
		minimap->player_pos.y0 -= PLAYER_STEP;
	}
	else
	{
		// minimap->player_pos.x0 -= (minimap->player_delta_x / 5);
		// minimap->player_pos.y0 -= (minimap->player_delta_y / 5);
		// minimap->player_pos.x1 -= (minimap->player_delta_x / 5);
		// minimap->player_pos.y1 -= (minimap->player_delta_y / 5);
		minimap->player_pos.y0 += PLAYER_STEP;
	}
	set_player_direction(minimap);
	mlx_clear_window(game->mlx, game->win);
	minimap->map.img = mlx_new_image(game->mlx, 200, 200);
	minimap->map.addr = mlx_get_data_addr(minimap->map.img, &minimap->map.bpp, &minimap->map.size,
										  &minimap->map.endian);
	init_minimap(minimap, false);
	draw_minimap(minimap);
	mlx_put_image_to_window(game->mlx, game->win, minimap->map.img, 0, 0);
}

int deal_key(int key, t_game *game)
{
	if (key == 53)
		close_win(game);
	else if (key >= 123 && key <= 126)
	{
		player_movement(key, game);
	}
	return (0);
}

int main(void)
{
	t_game game;
	// t_minimap *minimap;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1000, 900, "cub3D");
	game.minimap = (t_minimap *)malloc(sizeof(t_minimap));
	init_minimap(game.minimap, true);
	display_minimap(&game, game.minimap);
	mlx_put_image_to_window(game.mlx, game.win, game.minimap->map.img, 0, 0);
	mlx_key_hook(game.win, deal_key, &game);
	mlx_loop(game.mlx);
}