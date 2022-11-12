/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:28:49 by hyap              #+#    #+#             */
/*   Updated: 2022/11/09 18:53:36 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "main.h"

/* ft_split.c */
char		**ft_split(char *s, char c);
int			get_splits_no(char	**splits);
void		free_splits(char **splits);
/* utils.c */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
/* map_utils.c */
int			is_space(char **lines, t_int_pos pos);
int			is_wall_door(char **lines, t_int_pos pos);
int			is_player(char **lines, t_int_pos pos);
int			is_floor(char **lines, t_int_pos pos);
int			is_map_element(char **lines, t_int_pos pos);
/* map_utils_2.c */
char		**remalloc_map(t_game *game, char **lines);
/* parsing_utils.c */
int			is_wall_element(char *s);
int			is_fnc_element(char *s);
int			is_str_digit(char *s);
int			is_duplicated_element(char *s);
int			get_file_line_no(char *map_path);
/* render_utils.c */
void		set_player_direction(t_game *game);
void		get_start_pt(t_game *game);
int			get_color(char **map, t_double_pos dpos);
void		save_img_addr(t_img *img);
double		deg_to_rad(double degree);
/* render_utils_2.c */
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		better_angle(double *angle);
uint32_t	get_tex_color(t_img *data, int x, int y);
/* exit.c */
void		exit_error(const char *s);

double ft_sqr(double num);
#endif
