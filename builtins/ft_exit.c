/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:14:05 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/18 17:24:24 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void ft_exit(t_data *list)
{
    int i;

    i = -1;
    if (!list->commands->arguments[0])
        exit(1);
    else if (list->commands->arguments[1])
        printf("minishell: exit: too many arguments\n");
    else
    {
        while (list->commands->arguments[0][++i])
        {
            if (ft_isalpha(list->commands->arguments[0][i]))
            {
                printf("minishell: exit: %s: numeric argument required\n", list->commands->arguments[0]);
                exit(255);
            }
        }
        exit(ft_atoi(list->commands->arguments[0]));
    }
}