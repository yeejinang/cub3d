/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:07:10 by hyap              #+#    #+#             */
/*   Updated: 2022/11/10 14:44:43 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "container.h"

/* key_hooks.c */
int		handle_keypress(int key, t_game *game);
/* minimap.c */
void	draw_minimap(t_game *game);
/* dda_line.c */
void	dda_line(t_matrix matrix, t_game *game);
/* raycasting_texture.c */
void	draw_texture(t_game *game, t_raycast *rc, int elem);
/* raycasting.c */
void	draw_3D(t_game *game);
/* floor_n_ceiling.c */
void	draw_floor_n_ceiling(t_img *img, int color, int start_y, int end_y);
/* weapon.c */
void	init_weapon(t_game *game, t_weapons *weapons);
void	draw_weapon(t_game *game);
void	handle_door(t_game *game);
void	dda_3D(t_game *game, t_raycast *rc, int x);
t_img    copy_image(t_game *game, t_img img);
#endif