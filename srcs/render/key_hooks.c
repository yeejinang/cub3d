/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:10:18 by hyap              #+#    #+#             */
/*   Updated: 2022/11/12 17:16:34 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void handle_movements(int key, t_game *game)
{
	double angle;
	t_int_pos tmp;

	angle = game->player_pos.angle;
	if (key == A_BTN)
		angle = (int)(game->player_pos.angle + 90) % 360;
	else if (key == D_BTN)
		angle = (int)(game->player_pos.angle - 90) % 360;
	if (key != S_BTN)
	{
		tmp.x = game->player_pos.pos.x0 + cos(deg_to_rad(angle)) * PLAYER_STEP;
		tmp.y = game->player_pos.pos.y0 - sin(deg_to_rad(angle)) * PLAYER_STEP;
		if (is_wall_door(game->map, tmp) == 0 || is_wall_door(game->map, tmp) == 3)
		{
			game->player_pos.pos.x0 += cos(deg_to_rad(angle)) * PLAYER_STEP;
			game->player_pos.pos.y0 -= sin(deg_to_rad(angle)) * PLAYER_STEP;
		}
		return;
	}
	tmp.x = game->player_pos.pos.x0 - cos(deg_to_rad(angle)) * PLAYER_STEP;
	tmp.y = game->player_pos.pos.y0 + sin(deg_to_rad(angle)) * PLAYER_STEP;
	if (is_wall_door(game->map, tmp) == 0 || is_wall_door(game->map, tmp) == 3)
	{
		game->player_pos.pos.x0 -= cos(deg_to_rad(angle)) * PLAYER_STEP;
		game->player_pos.pos.y0 += sin(deg_to_rad(angle)) * PLAYER_STEP;
	}
}

void handle_angle(int key, t_game *game)
{
	if (key == LEFT_BTN)
	{
		game->player_pos.angle += 5;
		if (game->player_pos.angle > 360)
			game->player_pos.angle -= 360;
	}
	else if (key == RIGHT_BTN)
	{
		game->player_pos.angle -= 5;
		if (game->player_pos.angle < 0)
			game->player_pos.angle += 360;
	}
}

int handle_keypress(int key, t_game *game)
{
	if (key == OPEN_DOOR_BTN)
	{
		game->door_status = DOOR_OPEN;
		printf("door status, open door on press: %d\n", game->door_status);
	}
	if (key == CLOSE_DOOR_BTN)
		game->door_status = DOOR_CLOSE;
	// if (game->door_status == OPEN || game->door_status == CLOSE)
	// 	handle_door(game);
	if (key == W_BTN || key == S_BTN || key == A_BTN || key == D_BTN)
		handle_movements(key, game);
	handle_angle(key, game);
	if (key == E_BTN && game->weapons.status == CLOSED)
		game->weapons.status = OPENED;
	else if (key == E_BTN && game->weapons.status == OPENED)
		game->weapons.status = CLOSED;
	set_player_direction(game);
	return (0);
}