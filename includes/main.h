/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:16:41 by hyap              #+#    #+#             */
/*   Updated: 2022/11/07 18:44:18 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "container.h"
# include "utils.h"
# include "parsing.h"
# include "render.h"
/* Keycodes */
# define ESC_BTN 53
# define RIGHT_BTN 124
# define LEFT_BTN 123
# define W_BTN 13
# define A_BTN 0
# define S_BTN 1
# define D_BTN 2
# define PLAYER_STEP 0.25
# define SCALE 20
# define FOV 66.0
# define TEXSIZE 64
/* Window px size */
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
/* Minimap max tiles */
# define MI_WIDTH 10
# define MI_HEIGHT 10
/* Minimap max px */
# define MI_PX_WIDTH 200
# define MI_PX_HEIGHT 200
/* Floor/Ceiling size */
# define FC_WIDTH WIN_WIDTH / 2
# define FC_HEIGHT WIN_HEIGHT / 2
/* Colors */
# define GREEN 0x7FFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define ORANGE 0xFC9403
/* Images */
# define _MINIMAP_IMG 1
# define _FLOOR_IMG 2
# define _CEILING_IMG 3
# define _3D_IMG 4 

#endif
