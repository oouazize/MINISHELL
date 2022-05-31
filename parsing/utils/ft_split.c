/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:28:18 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 13:37:25 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[count])
		count++;
	if (size == 0)
		return (count);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}

static int	ft_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_counter(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = ft_word(s, c);
		s += i;
		if (i > 0)
			word++;
	}
	return (word);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*first;
	unsigned char	*second;

	i = 0;
	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (first[i] && second[i] && first[i] == second[i])
		i++;
	return (first[i] - second[i]);
}

char	**ft_split(char *s, char c)
{
	int		string;
	int		count;
	int		len;
	char	**tab;

	if (!s)
		return (0);
	string = ft_counter(s, c);
	tab = (char **)malloc((string + 1) * sizeof(char *));
	if (!tab)
		return (0);
	count = -1;
	while (++count < string)
	{
		while (*s && *s == c)
			s++;
		len = ft_word(s, c);
		tab[count] = (char *)malloc((len + 1) * sizeof(char));
		if (!tab[count])
			return (0);
		ft_strlcpy(tab[count], s, len + 1);
		s += len;
	}
	tab[string] = 0;
	return (tab);
}
