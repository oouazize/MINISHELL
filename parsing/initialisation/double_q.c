/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:05:26 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/13 17:19:40 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int d)
{
	if (d >= 48 && d <= 57)
		return (1);
	else
		return (0);
}

char *dlr_path(char *env, t_node *en)
{
    while(en)
    {
        if (ft_strcmp(en->name, env) == 0)
            return (en->path);
        en = en->next;
    }
    return (0);
}

void	dollar_q(char *line, char **str, int *i, t_node *en)
{
    char *env;

    env = NULL;
    if (line[++(*i)] == '?')
    {
        *str = ft_strjoin(*str, ft_itoa(exit_status));
        exit_status = 0;
        (*i)++;
    }
	else if (line[*i] == '_' || ft_isdigit(line[*i]) || ft_isalpha(line[*i]))
    {
        env = ft_chrjoin(NULL, line[(*i)]);
        (*i)++;
        while (line[*i] == '_' || ft_isdigit(line[*i]) || ft_isalpha(line[*i]))
        {
            env = ft_chrjoin(env, line[*i]);
            (*i)++;
        }
		if (dlr_path(env, en) == 0)
			*str = ft_strjoin(*str, "");
		else
        	*str = ft_strjoin(*str, dlr_path(env, en));
    }
}

int dollar(char *line, char **str, int *i, t_node *en)
{
    char *env;
    
    env = NULL;
    if (line[++(*i)] == '?')
    {
        *str = ft_strjoin(*str, ft_itoa(exit_status));
        exit_status = 0;
        (*i)++;
    }
	else if (line[*i] != '_' && !ft_isdigit(line[*i]) && !ft_isalpha(line[*i]))
		return (2);
	else if (line[*i] == 0)
	{
        *str = ft_chrjoin(*str, line[--(*i)]);
		(*i)++;
	}
    else
    {
        env = ft_chrjoin(NULL, line[*i]);
        (*i)++;
        while (line[*i] != 34 && line[*i] != 32 && line[*i] != 39 && line[*i])
        {
            env = ft_chrjoin(env, line[*i]);
            (*i)++;
        }
        *str = ft_strjoin(*str, dlr_path(env, en));
    }
    if(!line[*i])
		return (2);
    return (0);
}

int double_q(char *line, char **str, int *i, t_node *en)
{
    if (line[*i] == 34)
    {
        (*i)++;
        while (line[*i] && line[*i] != 34)
        {
				printf(".%s\n", *str);
            if(line[*i] == '$')
			{
				dollar_q(line, str, i, en);
			}
            else
            {
                *str = ft_chrjoin(*str, line[*i]);
                (*i)++;
            }
        }
        if (!line[*i])
            return (1);
    }
    else
    {
        if (dollar(line, str, i, en) == 2)
            return (2);
        else if (dollar(line, str, i, en) == 1)
            (*i)--;
    }
    return (0);
}