/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:10 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 19:58:14 by oouazize         ###   ########.fr       */
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

void    echo(t_data *list, int k)
{
    int i;
    int flag;

    i = -1;
    flag = 0;
    if (!list->commands[k].arguments[0])
            printf("\n");
    while (list->commands[k].arguments[++i])
    {
        if (ft_cmpecho(list->commands[k].arguments[i]))
        {
            i++;
            flag = 1;
            while (ft_cmpecho(list->commands[k].arguments[i]))
                i++;
        }
        if (flag)
        {
			printf("%s\n", list->commands[k].arguments[i]);
            //write(list->commands->std_out, list->commands->arguments[i], ft_strlen(list->commands->arguments[i]));
            if (list->commands[k].arguments[i + 1] != NULL)
				printf(" ");
            //write(list->commands->std_out, " ", 1);
        }
        else
        {
			printf("%s\n", list->commands[k].arguments[i]);
			//write(list->commands->std_out, list->commands->arguments[i], ft_strlen(list->commands->arguments[i]));
            if (list->commands[k].arguments[i + 1] == NULL)
            	printf("\n");
            else
                printf(" ");
        }
    }
    return ;
}