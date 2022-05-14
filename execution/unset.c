/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:04:36 by oouazize          #+#    #+#             */
/*   Updated: 2022/04/03 17:17:03 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_node(t_node **en, char *s)
{
    t_node *prv;
    t_node *ptr;

    prv = *en;
    if (ft_strcmp(prv->name, s) == 0)
        *en = (*en)->next;
    else
    {
        while (prv)
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

void	unset(char *read, t_node **en)
{
    char **spl;
	int j = 0;

    spl = ft_split(read, ' ');
    if (ft_strcmp(spl[0], "unset") != 0)
    {
        printf("my shell: %s: command not found\n", spl[0]);
        return ;
    }
    while(spl[++j])
        remove_node(en, spl[j]);
}


    // char **spl;
    // t_node  *new;
    // int i = -1;
    // int j = -1;
    // int size;

    // while (env[++i])
    // {}
    // size = i;
    // i = 0;
    // // if (!flag)
	// // {
    // //     while (size-- > 0)
	// //     {
	// //     	new = ft_lstnew(env[i++]);
	// //     	ft_lstadd_back(en, new);
	// //     }
    // // }
    // i = 0;
    // spl = ft_split(read, ' ');
    // if (ft_strcmp(spl[0], "unset") != 0)
    // {
    //     printf("my shell: %s: command not found\n", spl[0]);
    //     return ;
    // }
    // while (spl[++i])
    // {
    //     j = -1;
    //     while (spl[i][++j])
    //     {}
    //     spl[i][j++] = '=';
    //     spl[i][j] = '\0';
	// 	//printf("sssss\n");
	// 	while (spl[++i])
    //     	remove_node(en, spl[i]);
	// 	//printf("sssss\n");
		
    // }