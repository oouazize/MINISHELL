/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:50 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 13:25:25 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    cd(t_data *list)
{
    if (!list->commands->arguments[0] || ft_strcmp(list->commands->arguments[0], "~") == 0)
    {
        if (chdir(getenv("HOME")) != 0)
            return ;
    }
    else
    {
        if (chdir(list->commands->arguments[0]) != 0)
        {
            printf("my shell: cd: %s: %s\n", list->commands->arguments[0], strerror(errno));
            exit_status = 1;
            return ;
        }
    }
    return ;
}