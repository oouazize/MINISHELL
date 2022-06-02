/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:58:08 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 19:16:07 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell1.h"

void	ft_wait_pid(t_pipes *pipes, t_data *data)
{
	int	i;

	i = 0;
	g_manager.f_status = 0;
	while (i < data->number_of_commands)
		waitpid(pipes->pid[i++], &g_manager.f_status, 0);
	if (!g_manager.exit_status)
		g_manager.exit_status = g_manager.f_status / 256;
}

void	ft_dup_exec(t_data **data, t_pipes *pipes, int i)
{
	pipes->in = 0;
	pipes->out = 1;
	if ((*data)->commands[i].std_in > 2)
		pipes->in = (*data)->commands[i].std_in;
	else if (i != 0)
		pipes->in = pipes->pipefd[i - 1][0];
	if ((*data)->commands[i].std_out > 2)
		pipes->out = (*data)->commands[i].std_out;
	else if (i != (*data)->number_of_commands - 1)
		pipes->out = pipes->pipefd[i][1];
	dup2(pipes->in, 0);
	dup2(pipes->out, 1);
}

void	ft_print(t_data **data, char *path, int i)
{
	if (!ft_strcmp(path, "NO"))
	{
		printf("minishell: %s: No such file or directory\n",
			(*data)->commands[i].command);
		g_manager.exit_status = 1;
		exit(1);
	}
	else
		printf("minishell: %s: command not found\n",
			(*data)->commands[i].command);
}

void	ft_exec(t_node **envs, t_data **data, int i)
{
	char	*path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	path = ft_path(*envs, (*data)->commands[i].command, cwd);
	free(cwd);
	if (!(*data)->commands[i].command && ((*data)->commands[i].std_in
			|| (*data)->commands[i].std_out || (*data)->commands[i].here_doc))
		exit(0);
	if (execve(path, tjoin((*data)->commands[i].command,
				(*data)->commands[i].arguments), env_to_char(*envs)) == -1)
	{
		ft_print(data, path, i);
		(*data)->error = 1;
		g_manager.exit_status = 127;
		exit(127);
	}
	exit(0);
}
