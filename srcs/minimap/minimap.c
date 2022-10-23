#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minimap.h"

/* display minimap player in center (N, S, E or W)
 ** get map start x and y
 ** start x = player.x - 5
 **			case if player is at the corner
 **			check if (player.x - 5 < 0 || player.x + 5 > map.height)
 **				then start x = 0 || start x = map.height - 10
 */

#define mapWidth 24
#define mapHeight 24

char *map[15] = {
	"111111111111111",
	"101000000000001",
	"101000000000001",
	"101000000000001",
	"100000000011101",
	"100001000N00010",
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

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	init_minimap(t_minimap *minimap)
{
	t_int_pos pos;

	// Assumption
	minimap->height = 200; // size in pixel
	minimap->width = 200; // size in pixel
	pos.y = 0;
	// Assumption
	int map_width = 15;
	int map_height = 15;

	while (pos.y < map_height)
	{
		pos.x = 0;
		while (pos.x < map_width)
		{
			if (map[pos.y][pos.x] == 'N' || map[pos.y][pos.x] == 'S' \
				|| map[pos.y][pos.x] == 'E'  || map[pos.y][pos.x] == 'W')
			{
				minimap->player.x = pos.x;
				minimap->player.y = pos.y;
				printf("player x: %d\t player y: %d\n", minimap->player.x, minimap->player.y);
				if (pos.x - 5 < 0)
					minimap->start_x = 0;
				else if (pos.x + 5 > map_width)
					minimap->start_x = map_width - 11;
				else
					minimap->start_x = pos.x - 5;
				if (pos.y - 5 < 0)
					minimap->start_y = 0;
				else if (pos.y + 5 > map_height)
					minimap->start_y = map_height - 11;
				else
					minimap->start_y = pos.y - 5;
				break;
			}
			pos.x++;
		}
		pos.y++;
	}
	// printf("start_x: %d\t start_y: %d\n", minimap->start_x, minimap->start_y);
}

void	draw_minimap_block(t_minimap *minimap, int color, t_int_pos pos, t_int_pos *draw_size)
{
	t_int_pos box_size;
	// t_int_pos draw_size;
	t_int_pos count;

	box_size.y = minimap->height / 11;
	box_size.x = minimap->width / 11;
	count.y = 0;
	while (count.y < draw_size->y)
	{
		count.x = 0;
		while (count.x < draw_size->x)
		{
			my_mlx_pixel_put(&minimap->map, pos.x * draw_size->x + count.x, pos.y * draw_size->y + count.y, color);
			count.x++;
		}
		count.y++;
	}
}

// draw minimap for 11 * 11 map into 200 * 200 pixel
void	draw_minimap(t_minimap *minimap)
{
	t_int_pos pos;
	pos.y = 11;
	int color;
	t_int_pos draw_size;
	t_int_pos player_size;

	draw_size.y = minimap->height / 11;
	draw_size.x = minimap->width / 11;
	player_size.x = minimap->width / 30;
	player_size.y = minimap->height / 30;
	while (--pos.y >= 0)
	{
		pos.x = 11;
		while (--pos.x >= 0)
		{
			if (map[minimap->start_y + pos.y][minimap->start_x + pos.x] == '1')
				color = 0x58D68D;
			else if (map[minimap->start_y + pos.y][minimap->start_x + pos.x] == '0')
				color = 0xFFFFFF;
			else if (map[minimap->start_y + pos.y][minimap->start_x + pos.x] == ' ')
				color = 0x000000;
			// else
			// 	color = 0xEC7063;
			draw_minimap_block(minimap, color, pos, &draw_size);
		}
	}
	draw_minimap_block(minimap, 0xEC7063, minimap->player, &player_size);
}

void	display_minimap(t_game game, t_minimap *minimap)
{
	minimap->map.img = mlx_new_image(game.mlx, minimap->width, minimap->height);
	minimap->map.addr = mlx_get_data_addr(minimap->map.img, &minimap->map.bpp, &minimap->map.size,
								&minimap->map.endian);
	draw_minimap(minimap);
	mlx_put_image_to_window(game.mlx, game.win, minimap->map.img, 0, 0);
}

int main(void)
{
	t_game game;
	t_minimap *minimap;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1920, 1080, "cub3D");
	minimap = (t_minimap*)malloc(sizeof(t_minimap));
	init_minimap(minimap);
	display_minimap(game, minimap);

	mlx_put_image_to_window(game.mlx, game.win, minimap->map.img, 0, 0);
	mlx_loop(game.mlx);
}