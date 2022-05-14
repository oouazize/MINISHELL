/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:37:27 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 18:13:26 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    envp(char **env, t_node **en)
{
    t_node  *new;
    int i = -1;
    int size;

	//printf("%s\n", en);
    if (*en)
        i = 0;
    if (i == -1)
    {
        while (env[++i])
        {}
        size = i;
        i = 0;
        while (size-- > 0)
        {
            new = ft_lstnew(env[i++]);
            ft_lstadd_back(en, new);
        }
    }
}