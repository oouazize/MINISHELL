/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:14:14 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/13 08:45:29 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *edit_quote(char *line, t_node *en)
{
    int i;
    int retur;
    char *str;

    str = NULL;
    i = -1;
    while (line[++i])
    {
        if (line[i] == 39)
        {
            if (single_q(line, &str, &i))
                return (0);
        }
        else if (line[i] == 34 || line[i] == '$')
        {
            retur = double_q(line, &str, &i, en);
            if (retur == 1)
                return (0);
            else if (retur == 2)
                i--;
        }
        else
            str = ft_chrjoin(str, line[i]);
    }
    return (str);
}