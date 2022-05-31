/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:23:59 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 20:54:47 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(t_exp exp, t_data *data, t_node **en, int i)
{
	if (!data->commands[i].command)
		return (1);
	else if (ft_strcmp(data->commands[i].command, "echo") == 0)
		echo(data, i, 0);
	else if (ft_strcmp(data->commands[i].command, "cd") == 0)
		cd(data, en);
	else if (ft_strcmp(data->commands[i].command, "pwd") == 0)
		pwd(data, i);
	else if (ft_strcmp(data->commands[i].command, "env") == 0)
		print_env(data, *en, i);
	else if (ft_strcmp(data->commands[i].command, "unset") == 0)
		unset(data, en);
	else if (ft_strcmp(data->commands[i].command, "export") == 0)
		export(exp, data, en, i);
	else if (ft_strcmp(data->commands[i].command, "exit") == 0)
		ft_exit(data);
	else
		return (1);
	return (0);
}
