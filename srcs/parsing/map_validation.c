/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:13:25 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 12:27:45 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map_validation	init_map_validation_struct(int y, int x)
{
	t_map_validation	mv;
	
	mv.top.y = y - 1;
	mv.top.x = x;
	mv.bottom.y = y + 1;
	mv.bottom.x = x;
	mv.left.y = y;
	mv.left.x = x - 1;
	mv.right.y = y;
	mv.right.x = x + 1;
	mv.topleft.y = y - 1;
	mv.topleft.x = x - 1;
	mv.topright.y = y - 1;
	mv.topright.x = x + 1;
	mv.bottomleft.y = y + 1;
	mv.bottomleft.x = x - 1;
	mv.bottomright.y = y + 1;
	mv.bottomright.x = x + 1;
	return (mv);
}

int	is_valid_surrounding(char **lines, int y, int x, int l_no)
{
	int					has_open;
	t_map_validation	mv;
	(void)l_no;
	
	has_open = 0;
	mv = init_map_validation_struct(y, x);
	if (mv.top.y > 0 && (is_space(lines, mv.top) || is_player(lines, mv.top)))
		return (0);
	// if (mv.bottom.y < l_no && (is_space()))
	
	return (0);
}

int	is_valid_map(char **lines)
{
	t_int_pos	pos;
	int			l_no;

	pos.y = 0;
	l_no = get_splits_no(lines);
	while (lines[pos.y])
	{
		pos.x = 0;
		while (lines[pos.y][pos.x])
		{
			if (is_space(lines, pos) && !is_valid_surrounding(lines, pos.y, pos.x, l_no))
				return (0);
			pos.x++;
		}
		if (!is_valid_surrounding(lines, pos.y, pos.x, l_no))
			return (0);
		pos.y++;
	}
	return (1);
}
