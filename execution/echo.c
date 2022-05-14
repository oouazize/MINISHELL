/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:10 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/10 18:45:17 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    echo(t_data *data)
{
    char *path;
    int i = -1;
    int skip = 0;

    while (data->commands->arguments[++i])
    {
    	if (ft_cmpecho(data->commands->arguments[i]) == 0)
        {
            while (data->commands->arguments[i + 1])
            {
                skip = 1;
                printf("%s ", data->commands->arguments[i++]);
            }
            if (skip)
                printf("%s", data->commands->arguments[i]);
            else
                printf("%s\n", data->commands->arguments[i]);
            return ;
        }
    }
    return ;
}