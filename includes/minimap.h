/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:30:03 by yang              #+#    #+#             */
/*   Updated: 2022/10/21 19:16:27 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

#include "container.h"

typedef struct s_minimap 
{
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	t_int_pos player;
	t_img	map;
} t_minimap;

#endif