/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:10:46 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 14:50:48 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_data *data, t_node *en, int k)
{
	char	*str;

	str = "declare -x ";
	while (en)
	{
		write(data->commands[k].std_out, str, ft_strlen(str));
		if (en->egal == '+')
			write(data->commands[k].std_out, en->name, ft_strlen(en->name));
		else
		{
			write(data->commands[k].std_out, en->name, ft_strlen(en->name));
			write(data->commands[k].std_out, &en->egal, 1);
			write(data->commands[k].std_out, "\"", 1);
			write(data->commands[k].std_out, en->path, ft_strlen(en->path));
			write(data->commands[k].std_out, "\"", 1);
		}
		write(data->commands[k].std_out, "\n", 1);
		en = en->next;
	}
}

int	path_export(char *spl, t_exp *exp)
{
	if (spl[exp->i] == '+')
	{
		exp->egal = 1;
		if (spl[exp->i + 1] != '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n", spl);
			return (1);
		}
		else
			(exp->i)++;
		while (spl[++(exp->i)])
			exp->path = ft_chrjoin(exp->path, spl[exp->i]);
	}
	else if (spl[exp->i] == '=')
	{
		while (spl[++(exp->i)])
			exp->path = ft_chrjoin(exp->path, spl[exp->i]);
	}
	return (0);
}

int	change_path(t_node **ptr, t_exp *exp)
{
	if (!ft_strcmp((*ptr)->path, (*exp).path))
	{
		free((*exp).path);
		return (1);
	}
	if (g_manager.fois)
		free((*ptr)->path);
	(*ptr)->path = ft_strdup((*exp).path);
	g_manager.fois = 1;
	free((*exp).path);
	return (0);
}

int	push_in_path2(t_node **ptr, t_exp *exp)
{
	(*ptr)->egal = '=';
	if (!(*exp).path)
	{
		if (!ft_strcmp((*ptr)->path, ""))
		{
			free((*exp).path);
			return (1);
		}
		free((*ptr)->path);
		(*ptr)->path = ft_strdup("");
		g_manager.fois = 1;
		free((*exp).path);
	}
	else if (ft_strcmp((*exp).path, ""))
	{
		if (change_path(ptr, exp))
			return (1);
	}
	return (0);
}

void	push_in_path(t_node *ptr, t_exp exp)
{
	char	*pathi;

	if (exp.egal)
	{
		ptr->egal = '=';
		pathi = ft_strdup(ptr->path);
		if (g_manager.fois)
			free(ptr->path);
		ptr->path = ft_strjoin(pathi, exp.path);
		g_manager.fois = 1;
	}
	else if (exp.p)
	{
		if (push_in_path2(&ptr, &exp))
			return ;
	}
}
