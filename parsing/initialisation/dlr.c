/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:16:39 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 20:08:27 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	doollar2(char *line, char **str, int *i, t_node *en)
{
	char	*env;
	char	*envii;

	env = ft_strdup("");
	envii = env;
	free(envii);
	if (ft_isalpha(line[*i]) || line[*i] == '_')
	{
		env = ft_chrjoin(NULL, line[(*i)++]);
		while (ft_isalnum(line[*i]) || line[*i] == '_')
				env = ft_chrjoin(env, line[(*i)++]);
		*str = ft_strjoin(*str, dlr_path(env, en));
		envii = env;
		free(envii);
	}
	else if (line[*i] == 34 || line[*i] == 39)
		return (2);
	else
		*str = ft_chrjoin(*str, line[*i - 1]);
	return (0);
}

void	dollar2(char *line, char **str, int *i, t_node *en)
{
	char	*env;
	char	*envii;

	env = ft_strdup("");
	envii = env;
	free(envii);
	if (ft_isalpha(line[*i]) || line[*i] == '_')
	{
		env = ft_chrjoin(NULL, line[(*i)++]);
		while (ft_isalnum(line[*i]) || line[*i] == '_')
				env = ft_chrjoin(env, line[(*i)++]);
		*str = ft_strjoin(*str, dlr_path(env, en));
		envii = env;
		free(envii);
	}
	else
		*str = ft_chrjoin(*str, line[*i - 1]);
}

int	do48statusdigit(char *line, char **str, int *i)
{
	if (line[*i] == '?')
	{
		*str = ft_strjoin(*str, ft_itoa(g_manager.exit_status));
		g_manager.exit_status = 0;
		(*i)++;
	}
	else if (line[*i] == 48)
	{
		*str = ft_strjoin(*str, ft_strdup("minishell"));
		(*i)++;
	}
	else if (line[*i] == '$')
	{
		*str = ft_chrjoin(*str, line[*i]);
		(*i)++;
	}
	else
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	dollar(char *line, char **str, int *i, t_node *en)
{
	int	flag;

	flag = 0;
	if (*i < 0)
	{
		*i += 1000;
		flag = 1;
	}
	if (line[++(*i)] == '?' || line[*i] == 48 || line[*i] == '$'
		|| ft_isdigit(line[*i]))
	{
		if (do48statusdigit(line, str, i))
			return (2);
	}
	else
	{
		if (flag)
		{
			if (doollar2(line, str, i, en))
				return (2);
		}
		else
			dollar2(line, str, i, en);
	}
	return (0);
}
