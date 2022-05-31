/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:21:03 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 18:46:26 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	ft_beginning(char const *s1, char const *set)
{
	int	beg;
	int	i;

	beg = 0;
	i = 0;
	while (set[beg])
	{
		if (s1[i] == set[beg])
		{
			i++;
			if (!set[beg + 1])
				beg = '\0';
			else
				beg = 0;
		}
		else
			beg++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set, int len)
{
	int	end;

	end = 0;
	len -= 1;
	while (set[end])
	{
		if (s1[len] == set[end])
		{
			len--;
			if (!set[end + 1])
				end = '\0';
			else
				end = 0;
		}
		else
			end++;
	}
	return (len);
}

static char	*ft_alloc(char const *s1, int i, int len)
{
	int		t;
	char	*trim;

	t = 0;
	trim = (char *)malloc((len - i + 2) * sizeof(char));
	if (!trim)
		return (0);
	while (i <= len)
		trim[t++] = s1[i++];
	trim[t] = 0;
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		t;
	char	*trim;

	t = 0;
	i = 0;
	trim = NULL;
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = ft_beginning(s1, set);
	len = ft_end(s1, set, len);
	if (i > len)
	{
		trim = (char *)malloc(sizeof(char));
		trim[t] = 0;
		return (trim);
	}
	trim = ft_alloc(s1, i, len);
	if (!trim)
		return (NULL);
	free((void *)s1);
	return (trim);
}
