/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:49:37 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 15:14:01 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*string;
	int		len;
	int		len1;

	i = -1;
	j = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len = ft_strlen(s1);
	len1 = ft_strlen(s2);
	string = (char *)malloc((len + len1 + 1) * sizeof(char));
	if (string == NULL)
		return (0);
	while (s1[++i])
		string[i] = s1[i];
	while (s2[j])
		string [i++] = s2[j++];
	string[i] = '\0';
	free(s1);
	free(s2);
	return (string);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	int		l;
	char	*s2;

	i = 0;
	j = 0;
	l = 0;
	if (!s1)
		return (0);
	while (s1[l])
		l++;
	s2 = (char *)malloc(l + 1 * sizeof(char));
	if (s2 == NULL)
		return (0);
	while (s1[j])
		s2[i++] = s1[j++];
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*sbstr;
	char			*str;

	j = 0;
	str = (char *)s;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sbstr = malloc((len + 1) * sizeof(char));
	if (sbstr == NULL)
		return (0);
	while (j < len)
		sbstr[j++] = str[start++];
	sbstr[j] = '\0';
	return (sbstr);
}

int	ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return (0);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j])
		{
			if (s2[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
