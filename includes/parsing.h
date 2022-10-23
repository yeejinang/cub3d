/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:07:46 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 12:07:23 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "main.h"

/* parsing_utils.c */
int		is_wall_element(char *s);
int		is_fnc_element(char *s);
int		is_str_digit(char *s);
int		is_duplicated_element(char *s);
/* element_validation.c */
void	validate_extension(char *map_path);
int		is_valid_elements(char ***lines);
/* map_validation.c */
int		is_valid_map(char **lines);
/* validation.c */
int		is_valid_file_content(char **lines);
/* parse.c */
void	parse(t_game *game, char *map_path);

#endif