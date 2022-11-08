/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:43:17 by marvin            #+#    #+#             */
/*   Updated: 2021/05/10 17:43:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *s)
{
	int		i;
	char	*line;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_remainder(char *save)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	remainder = (char *)malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	if (!remainder)
		return (NULL);
	j = 0;
	while (save[i])
		remainder[j++] = save[i++];
	remainder[j] = '\0';
	free(save);
	return (remainder);
}

int	check_ret(int ret, char *buf)
{
	if (ret == -1)
	{
		free(buf);
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*save;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	ret = 1;
	while (!check_nl(save, '\n') && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (!check_ret(ret, buf))
			return (-1);
		buf[ret] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	*line = get_line(save);
	save = get_remainder(save);
	if (ret == 0)
		return (0);
	return (1);
}
