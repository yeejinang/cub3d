/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:09:53 by hyap              #+#    #+#             */
/*   Updated: 2022/11/13 13:56:10 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
#define CONTAINER_H

typedef struct s_game t_game;
typedef struct s_elements t_elements;
typedef struct s_map_validation t_map_validation;
typedef struct s_int_pos t_int_pos;
typedef struct s_img t_img;
typedef struct s_color t_color;
typedef struct s_minimap t_minimap;
typedef struct s_texture t_texture;
typedef struct s_matrix t_matrix;
typedef struct s_player t_player;
typedef struct s_double_pos t_double_pos;
typedef struct s_raycast t_raycast;
typedef struct s_weapons t_weapons;

enum door_status
{
	DOOR_OPEN,
	DOOR_OPENING,
	DOOR_OPENED,
	DOOR_CLOSE,
	DOOR_CLOSING,
	DOOR_CLOSED,
};

struct s_color
{
	int r;
	int g;
	int b;
};

struct s_img
{
	void *img;
	char *addr;
	int bpp;
	int size;
	int x;
	int y;
	int endian;
};

struct s_int_pos
{
	int x;
	int y;
};

struct s_double_pos
{
	double x;
	double y;
};

struct s_texture
{
	t_int_pos tex_pos;
	double tex_start;
	double step;
	t_img img;
};

struct s_matrix
{
	double x0;
	double x1;
	double y0;
	double y1;
};

struct s_player
{
	t_matrix pos;
	double angle;
	char c;
};

struct s_minimap
{
	t_img img;
	t_matrix player_pos; // player_pos to facing direction
	double player_angle; // in degree
	t_int_pos size;
	t_int_pos pxsize;
	t_double_pos start;
	int line_len;
	double player_delta_x;
	double player_delta_y;
};

struct s_weapons
{
	int x;
	int y;
	int status;
	t_int_pos start_pos;
	t_img *images;
};

// struct s_door {
// 	int		door_status;
// 	t_img	prev_frame;
// };

struct s_game
{
	void *mlx;
	void *win;
	char **map;
	int f_color;
	int c_color;
	int door_status;
	t_img frame_door_close;
	t_img frame_door_open;
	t_img prev_frame;
	t_img wall_NO;
	t_img wall_SO;
	t_img wall_EA;
	t_img wall_WE;
	t_img door;
	t_int_pos map_size;
	t_minimap minimap;
	t_player player_pos;
	t_img img_3d;
	t_weapons weapons;
};

/* For checking duplicated elements
	by defining a static struct
*/
struct s_elements
{
	int had_NO;
	int had_SO;
	int had_WE;
	int had_EA;
	int had_F;
	int had_C;
};
/* For checking space surrounding */
struct s_map_validation
{
	int top;
	int bottom;
	int left;
	int right;
	int topleft;
	int topright;
	int bottomleft;
	int bottomright;
};
/* For raycasting use */
struct s_raycast
{
	t_matrix draw_ray;
	t_int_pos map_pos;
	t_int_pos step;
	t_int_pos ray_deduct;
	t_double_pos rayDir;
	t_double_pos sideDist;
	t_double_pos deltaDist;
	t_double_pos wall;
	t_texture texture;
	double perpWallDist;
	double angle;
	int line_height;
	int draw_start;
	int draw_end;
	int hit;
	int side;
};

#endif