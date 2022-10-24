/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:30:03 by yang              #+#    #+#             */
/*   Updated: 2022/10/23 14:58:40 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
#define MINIMAP_H

#include "container.h"

typedef struct s_minimap
{
	int width;
	int height;
	int start_x;
	int start_y;
	double player_x;
	double player_y;
	t_img map;
} t_minimap;

#endif