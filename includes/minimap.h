/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:30:03 by yang              #+#    #+#             */
/*   Updated: 2022/10/29 01:18:58 by yang             ###   ########.fr       */
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
} t_matrix;

typedef struct s_minimap
{
	double width;
	double height;
	int screen_width;
	int screen_height;
	double start_x;
	double start_y;
	t_matrix player_pos; // player_pos to facing direction
	int line_len;
	double scale;
	double player_delta_x;
	double player_delta_y;
	double player_angle; // in degree
	t_img map;
	t_img map_3d;
	// t_img floor;
	// t_img wall;
} t_minimap;

double deg_to_rad(double degree);

#endif