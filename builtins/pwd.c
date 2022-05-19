/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:25:29 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/18 17:46:00 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    pwd(void)
{
    char cwd[100];

    if (chdir("./") != 0)
        return ;
    else
    {
        if (getcwd(cwd, sizeof(cwd)) == 0)
            return ;
    }
    return ;
}