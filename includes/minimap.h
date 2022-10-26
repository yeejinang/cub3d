/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:30:03 by yang              #+#    #+#             */
/*   Updated: 2022/10/26 15:20:55 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
#define MINIMAP_H

#include "container.h"

#define PI 3.1415926535

typedef struct s_matrix
{
	double x0;
	double x1;
	double y0;
	double y1;
}	t_matrix;

typedef struct s_minimap
{
	double 		start_x;
	double 		start_y;
	t_matrix	player_pos; // player_pos to facing direction
	int			line_len;
	double 		scale;
	double 		player_delta_x;
	double 		player_delta_y;
	double 		player_angle; // in degree
	t_img 		map;
	t_img		floor;
	t_img		wall;
} t_minimap;

double deg_to_rad(double degree);

#endif