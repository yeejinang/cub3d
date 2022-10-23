/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:36:12 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 12:10:19 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Check extension .cub and filename exist */
void	validate_extension(char *map_path)
{
	int		i;
	char	*file;
	
	i = ft_strlen(map_path) - 1;
	while (map_path[i] && map_path[i] != '/')
		i--;
	if (map_path[i] == '/')
		i++;
	else
		i = 0;
	file = &map_path[i];
	i = 0;
	while (file[i])
	{
		if (file[i] == '.' && i != 0)
			break ;
		i++;
	}
	if (!file[i])
		exit_error("Missing extension !\n");
	if (ft_strncmp(&file[++i], "cub", 3) != 0)
		exit_error("Invalid extension !\n");
}

int	is_asset_exist(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	// printf("file: %s\n", file);
	if (fd < 0)
		return (0);
	return (1);
}

int	is_valid_color(char *color)
{
	char	**splits;
	int		i;
	int		has_err;
	
	splits = ft_split(color, ',');
	i = 0;
	has_err = 0;
	if (get_splits_no(splits) != 3)
		has_err = 1;
	while (splits[i] && !has_err)
	{
		if (!is_str_digit(splits[i]) || ft_strlen(splits[i]) > 3)
			has_err = 1;
		if (!has_err && (ft_atoi(splits[i]) > 255 || ft_atoi(splits[i]) < 0))
			has_err = 1;
		i++;
	}
	free_splits(splits);
	if (has_err)
		return (0);
	return (1);
}

int	is_valid_line(char *line)
{
	char	**splits;
	int		has_err;
	
	splits = ft_split(line, ' ');
	has_err = 0;
	if (get_splits_no(splits) != 2)
		has_err = 1;
	if (!has_err && !is_wall_element(splits[0]) && !is_fnc_element(splits[0]))
		has_err = 1;
	if (!has_err && is_wall_element(splits[0]) && (!is_asset_exist(splits[1]) || \
		is_duplicated_element(splits[0])))
		has_err = 1;
	if (!has_err && is_fnc_element(splits[0]) && (!is_valid_color(splits[1]) || \
		is_duplicated_element(splits[0])))
		has_err = 1;
	free_splits(splits);
	if (has_err)
	{
		printf("line: %s\n", line);
		return (0);
	}
	return (1);
}

int	is_valid_elements(char ***lines)
{
	int		has_err;
	int		el_count;
	
	has_err = 0;
	el_count = 0;
	while (**lines)
	{
		if ((**lines)[0] != '\0' && !is_valid_line(**lines) && el_count < 6)
			return (0);
		if ((**lines)[0] != '\0' && el_count < 6)
			el_count++;
		(*lines)++;
		if (el_count == 6)
			break ;
	}
	return (1);
}
