/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rechange.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:22:16 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 08:36:13 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **rechange(char **list)
{
    int i;
    int j;

    i = -1;
    while (list[++i])
    {
        j = -1;
        while(list[i][++j])
        {
            if (list[i][j] == 2)
                list[i][j] = 32;
            else if (list[i][j] == 6)
                list[i][j] = 39;
            else if (list[i][j] == 5)
                list[i][j] = 34;
            else if (list[i][j] == 4)
                list[i][j] = '<';
            else if (list[i][j] == 7)
                list[i][j] = '>';
            else if (list[i][j] == 1)
                list[i][j] = '|';
        }
    }
    return (list);
}