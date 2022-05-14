/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:38:14 by mmounib           #+#    #+#             */
/*   Updated: 2022/05/11 18:10:07 by mmounib          ###   ########.fr       */
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