/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:50 by oouazize          #+#    #+#             */
/*   Updated: 2022/03/16 15:24:03 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char *read)
{
    char *path;
    int i = -1;
    int x = 0;
    char **spl;

    spl = ft_split(read, ' ');
    if (ft_strcmp(spl[++i], "cd") != 0)
    {
        printf("my shell: %s: command not found\n", spl[i]);
        return ;
    }
    path = malloc(sizeof(char) * ft_strlen(read));
    while (spl[++i])
    {
        if (ft_strcmp(spl[i], "cd") == 0 && x == 0)
            x = 1;
        else
            path = spl[i];
    }
    if (!path[0])
    {
        if (chdir(getenv("HOME")) != 0)
            return ;
    }
    else
    {
        if (chdir(path) != 0)
        {
            printf("my shell: cd: %s: %s\n", path, strerror(errno));
            return ;
        }
    }
    return ;
}