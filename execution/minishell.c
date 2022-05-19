/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:14:46 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/17 16:37:15 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell1.h"

void ft_addhistory(char *line)
{
	int i;
	char cmd[4096];
	int cmdHisC =0; 
	char *cmdHistory;
	char *cmdsHistory[100];


    while(1) {
    /*** Read input from shell ***/
        fgets(cmd,4096,stdin);
		if(ft_strcmp(cmd,"") != 0)
		{
    		if((cmdHistory= ft_strdup(cmd)) != NULL)
    		{
        		if (cmdsHistory[cmdHisC] != NULL) 
        			free(cmdsHistory[cmdHisC]);

        		cmdsHistory[cmdHisC] = cmdHistory;
        		cmdHisC++;
   			}       
    		else
    			printf("ERROR!!\n");

    		if(cmdHisC>100)
        		cmdHisC=0;
		}
	}
}

char *get_path_env(t_node *env)
{
	while (env->name)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			return (env->path);
		env = env->next;
	}
	return (0);
}

char	*ft_path(t_node *envs, char *command, t_data **data)
{
	char	*pure_paths;
	char	**paths;
	char	*join;
	int i;
	int log = 1;

	i = 0;
	pure_paths = get_path_env(envs);
	paths = ft_split(pure_paths, ':');
	while(paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		join = ft_strjoin(paths[i], command);
		if(access(join, X_OK) == 0)
			return (join);
		i++;
	}
	// if (log == 1 && !flag)
	// {
	// 	write(2, "command not found\n", 18);
	// 	exit_status = 127;
	// }
	return (command);
}

// void sigintHandler(int signum, siginfo_t *siginfo, void *ptr)
// {
// 	if (signum == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// int main(int argc, char *argv[], char **env)
// {
// 	char *line;
// 	t_node *en;
// 	struct sigaction	sa;
// 	int flag;

// 	sa.sa_sigaction = &sigintHandler;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	flag = 0;
// 	while (1)
// 	{
// 		line = readline("My Shell : ");
// 		if (line == NULL)
// 			exit(0);
// 		envp(env, &en);
// 		add_history(line);
// 		if (ft_strcmp(line, "pwd") == 0)
//             pwd();
//         else if (ft_strstr(line, "echo") == 1)
//             echo(line);
//         else if (ft_strstr(line, "cd") == 1)
//             cd(line);
//         else if (ft_strstr(line, "env") == 1)
// 			print_env(en);
//         else if (ft_strstr(line, "unset") == 1)
//             unset(line, &en);
//         else if (ft_strstr(line, "export") == 1)
//             export(line, &en, &flag);
// 	}
// }