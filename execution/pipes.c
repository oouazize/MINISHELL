/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:08:32 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 19:10:02 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell1.h"

void	close_pipes(int (*pipes)[2], int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		if (i != index)
			close(pipes[i][1]);
		if (i != index - 1)
			close(pipes[i][0]);
		i++;
	}
}

void	ft_close_pipes1(t_pipes *pipes, t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->number_of_commands)
	{
		close(pipes->pipefd[i][0]);
		close(pipes->pipefd[i][1]);
		if ((*data)->commands[i].std_in > 0)
			close((*data)->commands[i].std_in);
		if ((*data)->commands[i].std_out > 1)
			close((*data)->commands[i].std_out);
		i++;
	}
}

int	ft_pipes1(t_exp exp, t_pipes *pipes, t_data **data, t_node **envs)
{
	if ((*data)->number_of_commands == 1)
	{
		if (builtins(exp, *data, envs, 0) == 1)
		{
			g_manager.flag_sig = 1;
			pipes->pid[0] = fork();
			if (pipes->pid[0])
				g_manager.flag_sig = -1;
			if (pipes->pid[0] == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				ft_dup_exec(data, pipes, 0);
				ft_exec(envs, data, 0);
			}
		}
		if ((*data)->commands[0].std_in > 0)
			close((*data)->commands[0].std_in);
		if ((*data)->commands[0].std_out > 1)
			close((*data)->commands[0].std_out);
		ft_wait_pid(pipes, *data);
		g_manager.flag_sig = 0;
		return (0);
	}
	return (1);
}

void	sig_pipe(t_pipes *pipes, int i)
{
	g_manager.flag_sig = 1;
	pipes->pid[i] = fork();
	if (pipes->pid[i])
		g_manager.flag_sig = -1;
}

void	ft_pipes(t_exp exp, t_pipes *pipes, t_data **data, t_node **envs)
{
	int	i;

	i = -1;
	if (g_manager.exit_status == 130 || ft_pipes1(exp, pipes, data, envs) == 0)
		return ;
	while (++i < (*data)->number_of_commands)
	{
		if (pipe(pipes->pipefd[i]) == -1)
			printf("ERROR!!!\n");
		sig_pipe(pipes, i);
		if (pipes->pid[i] == -1)
			printf("ERROR!!!\n");
		if (pipes->pid[i] == 0)
		{
			ft_dup_exec(data, pipes, i);
			close_pipes(pipes->pipefd, i);
			if (builtins(exp, *data, envs, i) == 1)
				ft_exec(envs, data, i);
			exit(0);
		}
	}
	close_wait_help(pipes, data);
}
