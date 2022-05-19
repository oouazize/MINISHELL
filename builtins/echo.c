/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:10 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/18 10:40:33 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int ft_cmpecho(char *s)
{
    int i = -1;

    if (s[++i] != '-')
        return (0);
    while (s[++i])
    {
        if (s[i] != 'n')
            return (0);
    }
    return (1);
}

void    echo(t_data *list)
{
    int i;
    int flag;

    i = -1;
    flag = 0;
    if (!list->commands->arguments[0])
            printf("\n");
    while (list->commands->arguments[++i])
    {
        if (ft_cmpecho(list->commands->arguments[i]))
        {
            i++;
            flag = 1;
            while (ft_cmpecho(list->commands->arguments[i]))
                i++;
        }
        if (flag)
        {
            write(list->commands->std_out, list->commands->arguments[i], ft_strlen(list->commands->arguments[i]));
            if (list->commands->arguments[i + 1] != NULL)
                write(list->commands->std_out, " ", 1);
        }
        else
        {
			write(list->commands->std_out, list->commands->arguments[i], ft_strlen(list->commands->arguments[i]));
            if (list->commands->arguments[i + 1] == NULL)
                write(list->commands->std_out, "\n", 1);
            else
                write(list->commands->std_out, " ", 1);
        }
    }
    return ;
}