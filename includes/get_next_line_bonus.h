/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:45:07 by marvin            #+#    #+#             */
/*   Updated: 2021/05/10 17:45:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# define BUFFER_SIZE 100

int		ft_strlen(char *s);
int		check_nl(char *s, char c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *save, char *buf);
int		get_next_line(int fd, char **line);

#endif