/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:08:32 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 19:55:04 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"
#include "minishell1.h"

void	ft_dup_exec(t_data **data, t_pipes *pipes, int i)
{
	int	flag;
	int k;

	flag = 0;
	k = 0;
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
	dup2(pipes->in,0);
	dup2(pipes->out,1);
}

void	ft_exec(t_node **envs, t_data **data, int i)
{
	if (!(*data)->commands[i].command && ((*data)->commands[i].std_in || (*data)->commands[i].std_out || (*data)->commands[i].here_doc))
		exit(0);
	if(execve(ft_path(*envs, (*data)->commands[i].command, data),
	tjoin((*data)->commands[i].command, (*data)->commands[i].arguments), env_to_char(*envs)) == -1)
	{
		printf("minishell: %s: command not found\n", (*data)->commands[i].command);
		(*data)->error = 1;
		exit_status = 127;
		exit(127);
	}
	exit(0);
}

void	ft_wait_pid(t_pipes *pipes, t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_commands)
	{
		waitpid(pipes->pid[i++], &exit_status, 0);
		exit_status /= 256;
	}
}

void	close_pipes(int (*pipes)[2], int index)
{
	int i;

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

void	ft_pipes(t_pipes *pipes, t_data **data, t_node **envs)
{
	int	i;

	i = 0;
	if ((*data)->number_of_commands == 1)
	{
		if (builtins(*data, envs, i) == 1)
		{
			pipes->pid[i] = fork();
			if (pipes->pid[i] == 0)
				ft_exec(envs, data, i);
		}
		ft_wait_pid(pipes, *data);
		return ;
	}
	
	while (i < (*data)->number_of_commands)
	{
		if (pipe(pipes->pipefd[i]) == -1)
			printf("ERROR!!!\n");
			pipes->pid[i] = fork();
			if (pipes->pid[i] == -1)
				printf("ERROR!!!\n");
			if (pipes->pid[i] == 0)
			{
				ft_dup_exec(data, pipes, i);
				close_pipes(pipes->pipefd, i);
				if (builtins(*data, envs, i) == 1)
					ft_exec(envs, data, i);
				exit(0);
			}
		i++;
	}
	i = 0;
	while (i < (*data)->number_of_commands)
	{
		close(pipes->pipefd[i][0]);
		close(pipes->pipefd[i][1]);
		if ((*data)->commands[i].std_in > 2)
			close((*data)->commands[i].std_in);
		if ((*data)->commands[i].std_out > 2)
			close((*data)->commands[i].std_out);
		i++;
	}
	ft_wait_pid(pipes, *data);
	
}