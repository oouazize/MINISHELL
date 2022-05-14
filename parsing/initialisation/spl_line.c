/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:07:32 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 08:36:19 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *spl_line(char *line)
{
    int i = -1;
    int len = 0;
    int start = 0;
    int flag = 0;
    int flag0 = 0;
    int flag2 = 0;
    int lock=0;
    char *str = NULL;
    while(line[++i])
    {
        if (!lock && flag0 && (line[i] == 32 || line[i] == 39 || line[i] == 34))
        {
            str = ft_strjoin(str, ft_substr(line, start, len));
            start = i + 1;
            len = 0;
            flag0 = 0;
        }
        else if (!lock && line[i] == 32 && flag == 0 && flag2 == 0)
        {
           str = ft_strjoin(str, ft_substr(line, start, len));
            start = i + 1;
            len = 0;
        }
        else if (line[i] == 39)
        {
            lock=1;
            flag++;
            if(flag == 1)
            {
                start = i + 1;
                len = 0;
            }
            if (flag > 1)
            {
               str = ft_strjoin(str, ft_substr(line, start, len));
                start = i + 1;
                len = 0;
                flag = 0;
                lock =0;
            }
        }
        else if (line[i] == 34 && flag == 0)
        {
            flag2++;
            lock=1;
            if(flag2 == 1)
            {
                start = i + 1;
                len = 0;
            }
            if (flag2 > 1)
            {
               str = ft_strjoin(str, ft_substr(line, start, len));
                start = i + 1;
                len = 0;
                lock =0;
                flag = 0;
            }
        }
        else
        {
            if (!lock && flag0 == 0 && line[i] != 32)
            {
                flag0 = 1;
                start = i;
                len = 0;
            }
            len++;
        }
    }
    if (flag0 && !line[i])
        str = ft_strjoin(str, ft_substr(line, start, len));
    return(str);
}