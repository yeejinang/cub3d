/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:09:34 by hyap              #+#    #+#             */
/*   Updated: 2022/10/20 20:05:31 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	string_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] == c)
		i++;
	if (!s[i])
		count = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

char	*store_string(char **s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (**s == c)
		(*s)++;
	while ((*s)[i] && (*s)[i] != c)
		i++;
	if (i == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	i = 0;
	while (**s && **s != c)
	{
		str[i++] = **s;
		(*s)++;
	}
	while (**s == c)
		(*s)++;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = string_count(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	split[count] = NULL;
	i = 0;
	while (*s)
		split[i++] = store_string(&s, c);
	return (split);
}

int	get_splits_no(char **splits)
{
	int	i;
	
	i = 0;
	while (splits[i])
		i++;
	return (i);
}

void	free_splits(char **splits)
{
	int	i;
	
	i = 0;
	while (splits[i])
		free(splits[i++]);
	free(splits);
}