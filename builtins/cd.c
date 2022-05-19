/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:50 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 15:39:48 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    cd(t_data *list)
{
    char *cwd;
    if (!list->commands->arguments[0] || ft_strcmp(list->commands->arguments[0], "~") == 0)
    {
        if (chdir(getenv("HOME")) != 0)
            return ;
    }
    else
    {
        if (chdir(list->commands->arguments[0]) != 0)
        {
            printf("minishell: cd: %s: %s\n", list->commands->arguments[0], strerror(errno));
            exit_status = 1;
            return ;
        }
        else
        {
			cwd = getcwd(NULL, 0);
            if (cwd == 0)
            {
                printf("cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
                return ;
            }
        }
    }
    return ;
}