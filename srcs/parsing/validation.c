/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:13:44 by hyap              #+#    #+#             */
/*   Updated: 2022/11/05 20:56:58 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		get_longest_strlen(char **lines)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(lines[0]);
	while (lines[i])
	{
		if (max < ft_strlen(lines[i]))
			max = ft_strlen(lines[i]);
		i++;
	}
	return (max);
}

int	is_valid_file_content(t_game *game, char **lines)
{
	char	**tmp;
	
	tmp = lines;
	if (!is_valid_elements(&tmp))
		return (0);
	while ((*tmp) && (*tmp)[0] == '\0')
		tmp++;
	if (!(*tmp))
		return (0);
	game->map_size.x = get_longest_strlen(tmp);
	game->map_size.y = get_splits_no(tmp);
	tmp = remalloc_map(game, tmp);
	if (!is_valid_map(game, tmp))
	{
		free_splits(tmp);
		return (0);
	}
	game->map = tmp;
	return (1);
}