/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 00:47:01 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 13:26:06 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    remove_node(t_node **en, char *s)
{
    t_node *prv;
    t_node *ptr;

    prv = *en;
    if (ft_strcmp(prv->name, s) == 0)
        *en = (*en)->next;
    else
    {
        while (prv->next)
        {
            if (ft_strcmp(prv->next->name, s) == 0)
            {
                ptr = prv->next;
                prv->next = ptr->next;
                ptr->next = NULL;
                free(ptr);
                break;
            }
            prv = prv->next;
        }
    }
    return ;
}
void    unset(t_data *list, t_node **en)
{
    int i = -1;

    while(list->commands->arguments[++i])
        remove_node(en, list->commands->arguments[i]);
}