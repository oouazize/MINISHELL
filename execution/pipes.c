#include "../parsing/minishell.h"
#include "minishell1.h"

void	ft_exec(t_node **envs, t_data *data, t_pipes *pipes, int i)
{
	//printf("%s\n", data->commands[i].command);
	char **join = malloc(sizeof(char *) * 2);
	int k = 0;
	// while (data ->commands[i].arguments[k])
	// 	printf("%s\n",data ->commands->arguments[k++]);
	pipes->in = 0;
	pipes->out = 1;
	if (data->commands[i].std_in > 2)
		pipes->in = data->commands[i].std_in;
	else if (i != 0)
		pipes->in = pipes->pipefd[i - 1][0];
	if (data->commands[i].std_out > 2)
		pipes->out = data->commands[i].std_out;
	else if (i != data->number_of_commands - 1)
		pipes->out = pipes->pipefd[i][1];
	//printf("MOK\n");
	//fprintf(stderr, "%d\n%d\n", pipes->in, pipes->out);
	// if (pipes->in == 0 || pipes->out == 1)
	// {
	// 	//printf("sssss\n");
	// 	// close(data->commands[i].std_in);
	// 	// close(data->commands[i].std_out);
	// 	dup2(pipes->in, STDIN_FILENO);
	// 	dup2(pipes->out, STDOUT_FILENO);
	// 	//fprintf(stderr, "%d\n%d\n", pipes->in, pipes->out);
	// 	//close(pipes->pipefd[i][0]);
	// 	//printf("%s\n", ft_path(envs, data->commands[i].command));
	// 	if(execve(ft_path(envs, data->commands[i].command),
	// 	tjoin(data->commands[i].command, data->commands[i].arguments), env_to_char(envs)) == -1)
	// 		printf("ERROR!!\n");
	// }
	//printf("%d %d\n",pipes ->in,pipes ->out);
	dup2(pipes->in,0);
	dup2(pipes->out,1);
	// fprintf(stderr, "%d\n%d\n", data->commands[i].std_in, data->commands[i].std_out);
	//close(pipes->pipefd[i][1]);
	if (!builtins(data, envs))
	{
		if(execve(ft_path(*envs, data->commands[i].command),
		tjoin(data->commands[i].command, data->commands[i].arguments), env_to_char(*envs)) == -1)
			printf("ERROR!!\n");
	}
	exit(0);
}

void	ft_wait_pid(t_pipes *pipes, t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_commands)
		waitpid(pipes->pid[i++],&data->status, 0);
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

void	ft_pipes(t_data *data, t_node **envs)
{
	t_pipes pipes;
	int i;

	i = 0;
	pipes.pipefd = malloc(sizeof(int *) * (data->number_of_commands));
	if (!pipes.pipefd)
		return ;
	pipes.pid = malloc(sizeof(int) * data->number_of_commands);
	while (i < data->number_of_commands)
	{
		if (pipe(pipes.pipefd[i]) == -1)
			printf("ERROR!!!\n");
		pipes.pid[i] = fork();
		if (pipes.pid[i] == -1)
			printf("ERROR!!!\n");
		if (pipes.pid[i] == 0)
		{
			close_pipes(pipes.pipefd, i);
			ft_exec(envs, data, &pipes, i);
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_commands)
	{
		close(pipes.pipefd[i][0]);
		close(pipes.pipefd[i][1]);
		if (data->commands[i].std_in > 2)
			close(data->commands[i].std_in);
		if (data->commands[i].std_out > 2)
			close(data->commands[i].std_out);
		// close(pipes.in);
		// close(pipes.out);
		//close(data->commands[i].std_in);
		i++;
	}
	ft_wait_pid(&pipes, data);
}