/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:41:27 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 11:31:44 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_space(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == ' ')
		return (1);
	return (0);
}

int	is_wall(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == '1')
		return (1);
	return (0);
}

int	is_player(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == 'N' || lines[pos.y][pos.x] == 'S' || \
		lines[pos.y][pos.x] == 'E' || lines[pos.y][pos.x] == 'W')
		return (1);
	return (0);
}

int	is_floor(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == '0')
		return (1);
	return (0);
}