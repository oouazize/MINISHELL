/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:23:59 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 18:03:52 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int    builtins(t_data *data, t_node **en, int i)
{
    if (!data->commands[i].command)
		return (1);
    else if (ft_strcmp(data->commands[i].command, "echo") == 0)
		echo(data, i);
    else if (ft_strcmp(data->commands[i].command, "cd") == 0)
        cd(data);
    else if (ft_strcmp(data->commands[i].command, "pwd") == 0)
        pwd();
    else if (ft_strcmp(data->commands[i].command, "env") == 0)
        print_env(*en);
    else if (ft_strcmp(data->commands[i].command, "unset") == 0)
        unset(data, en);
    else if (ft_strcmp(data->commands[i].command, "export") == 0)
        export(data, en);
    else if (ft_strcmp(data->commands[i].command, "exit") == 0)
        ft_exit(data);
	else
		return (1);
	return (0);
}