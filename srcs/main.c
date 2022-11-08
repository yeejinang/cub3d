/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:05:51 by hyap              #+#    #+#             */
/*   Updated: 2022/11/08 14:34:38 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_minimap(t_game *game)
{
	game->minimap.size.x = MI_WIDTH;
	if (game->map_size.x < MI_WIDTH)
		game->minimap.size.x = game->map_size.x;
	game->minimap.size.y = MI_HEIGHT;
	if (game->map_size.y < MI_HEIGHT)
		game->minimap.size.y = game->map_size.y;
	game->minimap.pxsize.x = game->minimap.size.x * SCALE;
	game->minimap.pxsize.y = game->minimap.size.y * SCALE;
	game->minimap.img.img = mlx_new_image(game->mlx, game->minimap.pxsize.x, \
											game->minimap.pxsize.y);
	save_img_addr(&(game->minimap.img));
	game->img_3d.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->img_3d));
	draw_floor_n_ceiling(&(game->img_3d), game->c_color, 0, WIN_HEIGHT / 2);
	draw_floor_n_ceiling(&(game->img_3d), game->f_color, \
							WIN_HEIGHT / 2, WIN_HEIGHT);
}

void	recreate_img(t_game *game)
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

int	render_frame(t_game *game)
{
	recreate_img(game);
	draw_minimap(game);
	draw_3D(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img_3d.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img.img, 0, 0);
	return (0);
}

void	init_game(t_game *game, char *map_path)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	parse(game, map_path);
	for (int i = 0; (game->map)[i]; i++)
		printf("%s\n", (game->map)[i]);
	printf("\n");
	printf("color_c: %d, color_f: %d\n", game->c_color, game->f_color);
	init_minimap(game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;
	
	if (ac != 2)
	{
		printf("./cub3d <path_to_map>\n");
		return (0);
	}
	init_game(&game, av[1]);
	// printf("NO addr: %p, x: %d, y: %d, size: %d\n", game.wall_NO.addr, game.wall_NO.x, game.wall_NO.y, game.wall_NO.size);
	// printf("SO addr: %p, x: %d, y: %d, size: %d\n", game.wall_SO.addr, game.wall_SO.x, game.wall_SO.x, game.wall_SO.size);
	// printf("WE addr: %p, x: %d, y: %d, size: %d\n", game.wall_WE.addr, game.wall_WE.x, game.wall_WE.x, game.wall_WE.size);
	// printf("EA addr: %p, x: %d, y: %d, size: %d\n", game.wall_EA.addr, game.wall_EA.x, game.wall_EA.x, game.wall_EA.size);
	// printf("\n");

	// printf("\n");
	// printf("Player x: %d, y: %d\n", game.player_pos.pos.x0, game.player_pos.pos.y0);
	// printf("\n");
	// printf("Map.x: %d, Map.y: %d\n", game.map_size.x, game.map_size.y);
	// printf("\n");
	// for (int i = 0; (game.map)[i]; i++)
	// 	printf("%s\n", (game.map)[i]);
	// mlx_key_hook(game.mlx, key_hook, &game);
	// mlx_loop(game.mlx);
	free_splits(game.map);
	// system("leaks cub3d");
	return (0);
}