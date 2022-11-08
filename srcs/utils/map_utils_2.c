/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:40:45 by hyap              #+#    #+#             */
/*   Updated: 2022/11/05 20:48:43 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**remalloc_map(t_game *game, char **lines)
{
	int		i;
	int		j;
	char	**new_map;
	
	i = 0;
	new_map = (char **)malloc(sizeof(char *) * (game->map_size.y + 1));
	new_map[game->map_size.y] = 0;
	while (lines[i])
	{
		new_map[i] = (char *)malloc(sizeof(char) * (game->map_size.x + 1));
		new_map[i][game->map_size.x] = '\0';
		j = -1;
		while (lines[i][++j])
			new_map[i][j] = lines[i][j];
		while (j < game->map_size.x)
			new_map[i][j++] = ' ';
		i++;
	}
	return (new_map);
}