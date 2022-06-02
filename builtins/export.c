/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:57:18 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 23:52:54 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_there2(t_exp *exp, char *spl, t_node **ptr)
{
	if (!ft_isalnum(spl[0]) && spl[0] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", spl);
		return (1);
	}
	while (spl[++((*exp).i)] && spl[(*exp).i] != '=' && spl[(*exp).i] != '+')
	{
		if (!ft_isalnum(spl[(*exp).i]) && spl[(*exp).i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", spl);
			return (1);
		}
		(*exp).name = ft_chrjoin((*exp).name, spl[(*exp).i]);
	}
	if_name(ptr, &(*exp));
	free((*exp).name);
	return (0);
}

int	if_there(t_exp exp, char *spl, t_node *ptr)
{
	if (if_there2(&exp, spl, &ptr))
		return (2);
	if (spl[exp.i])
	{
		if (path_export(spl, &exp))
			return (1);
	}
	else
		exp.p = 0;
	if (exp.flag)
	{
		push_in_path(ptr, exp);
		return (1);
	}
	else
		free(exp.path);
	return (0);
}

int	add_node(t_exp exp, t_node **en, char *spl)
{
	t_node	*new;
	int		i;

	spl = skip_quote(spl);
	i = if_there(exp, spl, *en);
	if (!i)
	{
		new = ft_lstnew(spl, justname(spl));
		ft_lstadd_front(en, new);
	}
	else if (i == 2)
		return (1);
	free(spl);
	return (0);
}

void	export(t_exp exp, t_data *list, t_node **en, int k)
{
	int	i;

	i = 0;
	if (!list->commands[k].arguments[i])
		sorting(*en, list, k);
	else if (!ft_isalpha(list->commands[k].arguments[i][0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n",
			list->commands[k].arguments[i]);
		g_manager.exit_status = 1;
		return ;
	}
	while (list->commands->arguments[i])
	{
		if (add_node(exp, en, list->commands[k].arguments[i++]))
			return ;
	}
}
