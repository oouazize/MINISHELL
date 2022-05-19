/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:54:17 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 15:59:46 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    print_env(t_node *en)
{
    while(en)
    {
        if(en->egal != '+')
            printf("%s%c%s\n", en->name, en->egal, en->path);
        en = en->next;
    }
}