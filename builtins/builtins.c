/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:23:59 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/13 08:28:49 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int    builtins(t_data *data, t_node **en)
{
    if (ft_strcmp(data->commands->command, "echo") == 0)
		echo(data);
    else if (ft_strcmp(data->commands->command, "cd") == 0)
        cd(data);
    else if (ft_strcmp(data->commands->command, "pwd") == 0)
        pwd();
    else if (ft_strcmp(data->commands->command, "env") == 0)
        print_env(*en);
    else if (ft_strstr(data->commands->command, "unset"))
        unset(data, en);
    else if (ft_strstr(data->commands->command, "export"))
        export(data, en);
	else
		return (0);
	return (1);
}