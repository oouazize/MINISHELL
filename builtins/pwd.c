/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:25:29 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 15:44:32 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    pwd(void)
{
    char *cwd;

    if (chdir("./") != 0)
        return ;
    else
    {
        cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			printf("minishell: %s\n", strerror(errno));
			return ;
		}
		printf("%s\n", cwd);
    }
    return ;
}