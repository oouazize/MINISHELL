/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:05:26 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 22:51:40 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*dlr_path(char *env, t_node *en)
{
	while (en)
	{
		if (ft_strcmp(en->name, env) == 0)
			return (ft_strdup(en->path));
		en = en->next;
	}
	return (0);
}

int	double_q2(char *line, char **str, int *i, t_node *en)
{
	if (line[*i] == '$')
	{
		if (dollar(line, str, i, en) == 2)
			return (1);
		else
			(*i)--;
	}
	else
		*str = ft_chrjoin(*str, line[*i]);
	return (0);
}

int	double_q(char *line, char **str, int *i, t_node *en)
{
	int	flag;

	flag = 0;
	*str = ft_strjoin(*str, ft_strdup(""));
	if (line[*i] == 34)
	{
		while (line[++(*i)] && line[*i] != 34)
		{
			if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
				flag = 1;
			if (double_q2(line, str, i, en))
				return (2);
		}
	}
	else
	{
		*i -= 1000;
		if (dollar(line, str, i, en) == 2)
			return (2);
		else
			(*i)--;
	}
	if (flag)
		*str = ft_chrjoin(*str, 1);
	return (0);
}
