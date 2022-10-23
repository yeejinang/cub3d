/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:00:51 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 12:07:03 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_duplicated_element(char *s)
{
	static t_elements	el = {0, 0, 0, 0, 0, 0};

	if (((ft_strncmp(s, "NO", 2) == 0) && el.had_NO) || \
		((ft_strncmp(s, "SO", 2) == 0) && el.had_SO) || \
		((ft_strncmp(s, "WE", 2) == 0) && el.had_WE) || \
		((ft_strncmp(s, "EA", 2) == 0) && el.had_EA) || \
		((ft_strncmp(s, "F", 1) == 0) && el.had_F) || \
		((ft_strncmp(s, "C", 1) == 0) && el.had_C))
		return (1);
	if (ft_strncmp(s, "NO", 2) == 0)
		el.had_NO = 1;
	else if (ft_strncmp(s, "SO", 2) == 0)
		el.had_SO = 1;
	else if (ft_strncmp(s, "WE", 2) == 0)
		el.had_WE = 1;
	else if (ft_strncmp(s, "EA", 2) == 0)
		el.had_EA = 1;
	else if (ft_strncmp(s, "F", 1) == 0)
		el.had_F = 1;
	else if (ft_strncmp(s, "C", 1) == 0)
		el.had_C = 1;
	return (0);
}

int	is_wall_element(char *s)
{
	// printf("s: %s\n", s);
	if (ft_strncmp(s, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(s, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(s, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(s, "EA", 2) == 0)
		return (1);
	return (0);
}

int	is_fnc_element(char *s)
{
	if (ft_strncmp(s, "F", 1) == 0)
		return (1);
	if (ft_strncmp(s, "C", 1) == 0)
		return (1);
	return (0);
}

int	is_str_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

