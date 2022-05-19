/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:05:26 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 16:18:34 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    else if (line[*i] == 48)
    {
        *str = ft_strjoin(*str, "minishell");
        (*i)++;
    }
    else if (line[*i] == '$')
    {
        *str = ft_strjoin(*str, ft_itoa(getpid()));
        (*i)++;
    }
    else if (ft_isdigit(line[*i]))
    {
        (*i)++;
        return (2);
    }
    else if (ft_isalpha(line[*i]) || line[*i] == '_')
    {
        env = ft_chrjoin(NULL, line[(*i)++]);
        while (ft_isalpha(line[*i]) || line[*i] == '_' || ft_isdigit(line[*i]))
            env = ft_chrjoin(env, line[(*i)++]);
        *str = ft_strjoin(*str, dlr_path(env, en));
    }
    else if (line[*i] == 34 || line[*i] == 39)
        return (0);
    else
        *str = ft_chrjoin(*str, line[*i - 1]);
    return (0);
}

int double_q(char *line, char **str, int *i, t_node *en)
{
    int flag = 0;
    *str = ft_strjoin(*str, ft_strdup(""));
    if (line[*i] == 34)
    {
        (*i)++;
        while (line[*i] && line[*i] != 34)
        {
            if (line[*i] == '>' || line[*i] == '<')
                flag = 1;
            if(line[*i] == '$')
			{
                if (dollar(line, str, i, en) == 2)
                    return (2);
                else
                    (*i)--;
            }
            else
                *str = ft_chrjoin(*str, line[*i]);
            (*i)++;
        }
        if (!line[*i] && line[*i - 1] != 34)
            return (1);
    }
    else
    {
        if (dollar(line, str, i, en) == 2)
            return (2);
        else
            (*i)--;
    }
    if (flag)
        *str = ft_chrjoin(*str, 1);
    return (0);
}