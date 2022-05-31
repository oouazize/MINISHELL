/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tjoin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:25:01 by mmounib           #+#    #+#             */
/*   Updated: 2022/05/29 15:00:57 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

void	if_name(t_node **ptr, t_exp *exp)
{
	while (*ptr)
	{
		if (ft_strcmp((*ptr)->name, exp->name) == 0)
		{
			exp->flag = 1;
			break ;
		}
		*ptr = (*ptr)->next;
	}
}

int	justname(char *spl)
{
	int	i;

	i = -1;
	while (spl[++i])
	{
		if (spl[i] == '=')
			return (0);
	}
	return (1);
}

char	**tjoin(char *s1, char **s2)
{
	int		len;
	char	**s3;

	len = 0;
	while (s2[len])
		len++;
	s3 = malloc(sizeof(char *) * (len + 2));
	s3[0] = s1;
	len = 0;
	while (s2[len])
	{
		s3[len + 1] = s2[len];
		len++;
	}
	s3[len + 1] = 0;
	return (s3);
}

char	*ft_chrjoin(char *s1, char c)
{
	int		i;
	char	*string;
	int		len;
	char	*s;

	i = -1;
	if (!s1)
	{
		s = malloc(sizeof(char) * 2);
		s[0] = c;
		s[1] = '\0';
		return (s);
	}
	len = ft_strlen(s1);
	string = (char *)malloc((len + 2) * sizeof(char));
	if (string == NULL)
		return (0);
	while (s1[++i])
		string[i] = s1[i];
	string [i++] = c;
	string[i] = '\0';
	free(s1);
	return (string);
}
