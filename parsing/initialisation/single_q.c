/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:06:04 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 08:36:16 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int single_q(char *line, char **str, int *i)
{
    int len;
    int start;

    len = 0;
    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != 39)
    {
        len++;
        (*i)++;
    }
    if (!line[*i])
        return (1);
    *str = ft_strjoin(*str, ft_substr(line, start, len));
    len = 0;
    return (0);
}
