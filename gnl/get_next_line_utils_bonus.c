/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:44:12 by marvin            #+#    #+#             */
/*   Updated: 2021/05/10 17:44:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_nl(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	if (s[i] == c)
		return (1);
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*string;
	int		i;

	if (!s)
		return (NULL);
	string = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_strjoin(char *save, char *buf)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!save && !buf)
		return (ft_strdup(""));
	if (!save)
		return (ft_strdup(buf));
	len = ft_strlen(save) + ft_strlen(buf);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (save[i])
		join[i++] = save[j++];
	j = 0;
	while (buf[j])
		join[i++] = buf[j++];
	join[i] = '\0';
	free(save);
	return (join);
}
