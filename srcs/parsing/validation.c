/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:13:44 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 11:31:09 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid_file_content(char **lines)
{
	char	**tmp;
	
	tmp = lines;
	if (!is_valid_elements(&tmp))
		return (0);
	while ((*tmp) && (*tmp)[0] == '\0')
		tmp++;
	// if (!is_valid_map(&tmp))
	// 	return (0);
	return (1);
}