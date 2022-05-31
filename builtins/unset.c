/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 00:47:01 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/30 13:17:19 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove(t_node *prv, char *s)
{
	t_node	*ptr;

	while (prv->next)
	{
		if (ft_strcmp(prv->next->name, s) == 0)
		{
			ptr = prv->next;
			prv->next = ptr->next;
			ptr->next = NULL;
			free(ptr->name);
			if (ft_strcmp(ptr->path, ""))
				free(ptr->path);
			free(ptr);
			break ;
		}
		prv = prv->next;
	}
}

void	remove_node(t_node **en, char *s)
{
	t_node	*prv;
	t_node	*tmp;

	prv = *en;
	if (ft_strcmp(prv->name, s) == 0)
	{
		tmp = *en;
		*en = (*en)->next;
		free(tmp->name);
		if (g_manager.fois)
			free(tmp->path);
		free(tmp);
	}
	else
		ft_remove(prv, s);
}

void	unset(t_data *list, t_node **en)
{
	int	i;

	i = -1;
	while (list->commands->arguments[++i])
		remove_node(en, list->commands->arguments[i]);
}
