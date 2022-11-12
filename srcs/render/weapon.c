/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:39:41 by hyap              #+#    #+#             */
/*   Updated: 2022/11/09 13:24:44 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_weapon(t_game *game, t_weapons *weapons)
{
	weapons->images = (t_img *)malloc(sizeof(t_img) * 5);
	(weapons->images)[0].img = mlx_xpm_file_to_image(game->mlx, WEAPON0, \
									&(weapons->x), &(weapons->y));
	save_img_addr(&((weapons->images)[0]));
	(weapons->images)[1].img = mlx_xpm_file_to_image(game->mlx, WEAPON1, \
									&(weapons->x), &(weapons->y));
	save_img_addr(&((weapons->images)[1]));
	(weapons->images)[2].img = mlx_xpm_file_to_image(game->mlx, WEAPON2, \
									&(weapons->x), &(weapons->y));
	save_img_addr(&((weapons->images)[2]));
	(weapons->images)[3].img = mlx_xpm_file_to_image(game->mlx, WEAPON3, \
									&(weapons->x), &(weapons->y));
	save_img_addr(&((weapons->images)[3]));
	(weapons->images)[4].img = mlx_xpm_file_to_image(game->mlx, WEAPON4, \
									&(weapons->x), &(weapons->y));
	save_img_addr(&((weapons->images)[4]));
	weapons->status = CLOSED;
	weapons->start_pos.x = WIN_WIDTH - weapons->x;
	weapons->start_pos.y = WIN_HEIGHT - weapons->y;
}

void	put_weapon(t_game *game, t_weapons *weapons, int *frame)
{
	mlx_put_image_to_window(game->mlx, game->win, weapons->images[*frame].img, \
		weapons->start_pos.x, weapons->start_pos.y);
	if (weapons->status == OPENED)
		(*frame)++;
	else if (weapons->status == CLOSED)
		(*frame)--;
	if (*frame > 4)
		*frame = 4;
	else if (*frame < 0)
		*frame = 0;
}

void	draw_weapon(t_game *game)
{
	static int	frame = 0;
	
	if (frame < 1)
		put_weapon(game, &(game->weapons), &frame);
	else if (frame < 2)
		put_weapon(game, &(game->weapons), &frame);
	else if (frame < 3)
		put_weapon(game, &(game->weapons), &frame);
	else if (frame < 4)
		put_weapon(game, &(game->weapons), &frame);
	else if (frame < 5)
		put_weapon(game, &(game->weapons), &frame);
}

