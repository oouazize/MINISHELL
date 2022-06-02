/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:21:03 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 12:14:39 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
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
	return (string);
}

static int	ft_start(char *s, char *set)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	while (s[i])
	{
		j = 0;
		d = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				d++;
			j++;
		}
		if (d == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_end(char *s, char *set)
{
	int	i;
	int	j;
	int	d;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		j = 0;
		d = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				d++;
			j++;
		}
		if (d == 0)
			break ;
		i--;
	}
	if (i == -1)
		i = (int)ft_strlen(s);
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*s;
	char	*p;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	s = (char *)s1;
	start = ft_start(s, (char *) set);
	end = ft_end(s, (char *) set);
	p = malloc(((end - start) + 2) * sizeof(char));
	if (p == NULL)
		return (0);
	i = 0;
	while (start <= end)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

void	close_wait_help(t_pipes *pipes, t_data **data)
{
	ft_close_pipes1(pipes, data);
	ft_wait_pid(pipes, *data);
	g_manager.flag_sig = 0;
}
