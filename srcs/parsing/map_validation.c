/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:13:25 by hyap              #+#    #+#             */
/*   Updated: 2022/11/07 14:00:31 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_perimeter(char **lines, int l_no, t_int_pos pos)
{
	if (pos.x == (ft_strlen(lines[pos.y]) - 1) || pos.x == 0 || \
		pos.y == 0 || pos.y == l_no - 1)
		return (1);
	return (0);
}

int	is_valid_surrounding(char **lines, int y, int x, int l_no)
{
	t_map_validation	mv;
	t_int_pos			pos;

	if (lines[y][x] == 'X' || lines[y][x] == '1')
		return (1);
	pos.y = y;
	pos.x = x;
	if (is_perimeter(lines, l_no, pos) || is_space(lines, pos))
		return (0);
	lines[y][x] = 'X';
	mv.left = is_valid_surrounding(lines, y, x - 1, l_no);
	mv.right = is_valid_surrounding(lines, y, x + 1, l_no);
	mv.top = is_valid_surrounding(lines, y - 1, x, l_no);
	mv.bottom = is_valid_surrounding(lines, y + 1, x, l_no);
	mv.topleft = is_valid_surrounding(lines, y - 1, x - 1, l_no);
	mv.topright = is_valid_surrounding(lines, y - 1, x + 1, l_no);
	mv.bottomleft = is_valid_surrounding(lines, y + 1, x - 1, l_no);
	mv.bottomright = is_valid_surrounding(lines, y + 1, x + 1, l_no);
	return (mv.top && mv.bottom && mv.left && mv.right && mv.topleft && \
		mv.topright && mv.bottomleft && mv.bottomright);
}

void	get_player_deg_n_dir(t_game *game)
{
	
	if (game->player_pos.c == 'E')
		game->player_pos.angle = 0;
	else if (game->player_pos.c == 'N')
		game->player_pos.angle = 90;
	else if (game->player_pos.c == 'W')
		game->player_pos.angle = 180;
	else if (game->player_pos.c == 'S')
		game->player_pos.angle = 270;
	set_player_direction(game);
}

int	is_valid_map_component(t_game *game, char **lines)
{
	t_int_pos	pos;
	t_int_pos	player_pos;
	
	pos.y = 0;
	player_pos.x = -1;
	while (lines[pos.y])
	{
		pos.x = 0;
		while (lines[pos.y][pos.x])
		{
			if (!is_map_element(lines, pos))
				return (0);
			if (is_player(lines, pos) && player_pos.x > -1)
				return (0);
			if (is_player(lines, pos) && player_pos.x == -1)
				player_pos = pos;
			pos.x++;
		}
		pos.y++;
	}
	if (player_pos.x == -1)
		return (0);
	game->player_pos.pos.x0 = (double)player_pos.x;
	game->player_pos.pos.y0 = (double)player_pos.y;
	game->player_pos.c = lines[player_pos.y][player_pos.x];
	get_player_deg_n_dir(game);
	return (1);
}

int	is_valid_map(t_game *game, char **lines)
{
	t_int_pos	pos;
	int			l_no;
	char		**tmp;

	if (!is_valid_map_component(game, lines))
		return (0);
	pos.y = -1;
	tmp = remalloc_map(game, lines);
	l_no = get_splits_no(tmp);
	while (tmp[++pos.y])
	{
		pos.x = -1;
		while (tmp[pos.y][++pos.x])
		{
			if (is_floor(tmp, pos) && \
				!is_valid_surrounding(tmp, pos.y, pos.x, l_no))
			{
				free_splits(tmp);
				return (0);
			}
		}
	}
	free_splits(tmp);
	return (1);
}
