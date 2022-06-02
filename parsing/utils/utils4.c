/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:48:30 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 12:15:43 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_redirection(t_data **data, char **list, int *i)
{
	if (list[*i + 1] == NULL || !ft_strcmp(list[*i + 1], "|")
		|| !ft_strcmp(list[*i + 1], "<")
		|| !ft_strcmp(list[*i + 1], ">") || !ft_strcmp(list[*i + 1], "<<")
		|| !ft_strcmp(list[*i + 1], ">>"))
	{
		if (list[*i + 1] == NULL)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%s'\n",
				list[++(*i)]);
		(*data)->error = 1;
		g_manager.exit_status = 258;
		return (1);
	}
	if (!ft_strcmp(list[*i + 1], ""))
	{
		printf("minishell: $%s: ambiguous redirect\n", g_manager.env_nopath);
		free(g_manager.env_nopath);
		(*data)->error = 1;
		g_manager.exit_status = 1;
		return (1);
	}
	return (0);
}

char	*skip_quote(char *s)
{
	int		i;
	char	*str;

	i = -1;
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (0);
	while (s[++i])
	{
		if (s[i] == '"')
			i++;
		else
			str[i] = s[i];
	}
	str[i] = '\0';
	return (str);
}

void	ft_swap(t_node *a, t_node *b)
{
	char	*temp;
	char	temp2;
	char	*temp3;

	temp = a->name;
	temp2 = a->egal;
	temp3 = a->path;
	a->name = b->name;
	a->egal = b->egal;
	a->path = b->path;
	b->name = temp;
	b->egal = temp2;
	b->path = temp3;
}

void	sorting(t_node *en, t_data *data, int k)
{
	int		swapped;
	t_node	*ptr1;
	t_node	*lptr;

	swapped = 1;
	lptr = NULL;
	if (en == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = en;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				ft_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	print_export(data, en, k);
}

char	*get_env(char *str, t_node *en)
{
	while (en)
	{
		if (!ft_strcmp(en->name, str))
			return (en->path);
		en = en->next;
	}
	return (0);
}
