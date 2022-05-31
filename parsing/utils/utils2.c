/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:47:16 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/30 10:19:47 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return ;
}

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
	return ;
}

int	lstnew2(char **name, char *data, t_node **new, int *i)
{
	*i = -1;
	*name = ft_strdup("");
	*new = malloc(sizeof(t_node));
	if (!(*new))
		return (0);
	while (data[++(*i)] && data[*i] != '=' && data[*i] != '+')
		*name = ft_chrjoin(*name, data[*i]);
	return (1);
}

void	lstnew3(t_node **new, char *name, char *path, int flag)
{
	if (flag)
		(*new)->egal = '+';
	else
		(*new)->egal = '=';
	if (!ft_strcmp(path, ""))
	{
		free(path);
		flag = 5;
	}
	(*new)->name = name;
	(*new)->path = path;
	if (flag == 5)
		(*new)->path = "";
	(*new)->next = NULL;
}

t_node	*ft_lstnew(char *data, t_node **en, int flag)
{
	t_node	*new;
	char	*name;
	char	*path;
	int		i;

	path = ft_strdup("");
	if (!lstnew2(&name, data, &new, &i))
		return (0);
	if (data[i] == '+')
	{
		if (data[i + 1] != '=')
		{
			free(path);
			exit (0);
		}
		else
			i++;
	}
	while (data[i] && data[++i])
		path = ft_chrjoin(path, data[i]);
	lstnew3(&new, name, path, flag);
	return (new);
}
