/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:05:51 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 14:14:25 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	key_hook(int keycode, t_game *game)
{
	(void)game;
	printf("key: %d\n", keycode);
	return (0);
}

void	init_game(t_game *game, char *map_path)
{
	// game->mlx = mlx_init();
	// game->win = mlx_new_window(game->mlx, 1920, 1080, "Test");
	parse(game, map_path);
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
	// mlx_key_hook(game.mlx, key_hook, &game);
	// mlx_loop(game.mlx);
	return (0);
}