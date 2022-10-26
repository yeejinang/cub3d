/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:09:53 by hyap              #+#    #+#             */
/*   Updated: 2022/10/24 13:30:53 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H

typedef	struct s_game			t_game;
typedef struct s_elements		t_elements;
typedef struct s_map_validation	t_map_validation;
typedef	struct s_int_pos		t_int_pos;
typedef struct s_img			t_img;
typedef struct s_color			t_color;
typedef struct s_minimap		t_minimap;

struct s_color {
	int	r;
	int	g;
	int b;
};

struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		size;
	int		x;
	int		y;
	int		endian;
};

struct s_game {
	void	*mlx;
	void	*win;
	char	**map;
	t_img	wall_NO;
	t_img	wall_SO;
	t_img	wall_EA;
	t_img	wall_WE;
	t_minimap	*minimap;
};
/* For checking duplicated elements 
	by defining a static struct
*/
struct s_elements {
	int	had_NO;
	int	had_SO;
	int	had_WE;
	int	had_EA;
	int	had_F;
	int	had_C;
};
struct s_int_pos {
	int	x;
	int	y;
};
/* For checking space surrounding */
struct s_map_validation {
	t_int_pos	top;
	t_int_pos	bottom;
	t_int_pos	left;
	t_int_pos	right;
	t_int_pos	topleft;
	t_int_pos	topright;
	t_int_pos	bottomleft;
	t_int_pos	bottomright;
};

#endif