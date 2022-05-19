/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:05:26 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 18:57:06 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    dol(char *line, char **str, int *i)
{
    int len = 0;
    int flag = 0;
    int j = *i + 1;
    int x = *i;
    if (line[j] == 34)
    {
        while(line[++j] && line[j] != 34)
            len++;
        *str = ft_strjoin(NULL, ft_substr(line, *i + 2, len));
        *i = j;
    }
    else
    {
        while(line[++x])
        {
            if (line[x] == 34)
                flag = 1;
        }
        if (flag)
        {
            while(line[*i])
            {
                if (line[*i] != 34)
                    *str = ft_chrjoin(*str, line[*i]);
                (*i)++;
            }
        }
        else
            *str = line;
    }
}

int non_dollar(char *line, char **str, int *i)
{
    int flag = 0;
    if (line[*i] == 34)
    {
        *str = ft_strjoin(*str, ft_strdup(""));
        (*i)++;
        while (line[*i] && line[*i] != 34)
        {
            if (line[*i] == '>' || line[*i] == '<')
                flag = 1;
            else
                *str = ft_chrjoin(*str, line[*i]);
            (*i)++;
        }
        if (!line[*i] && line[*i - 1] != 34)
            return (1);
        if (flag)
            *str = ft_chrjoin(*str, 1);
    }
    else
        dol(line, str, i);
    return (0);
}