/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:54:17 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 13:25:35 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void    print_env(t_node *en)
{
    while(en)
    {
        printf("%s%c%s\n", en->name, en->egal, en->path);
        en = en->next;
    }
}