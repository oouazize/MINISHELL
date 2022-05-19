/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:03:10 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 19:55:33 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sigintHandler(int signum, siginfo_t *siginfo, void *ptr)
{
	if (signum == SIGINT)
	{
        exit_status = 130;
		write(1,"\n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void    prompt(char *read, t_node **en, char **env, char ***list)
{
    while (ft_strcmp(read, "") == 0)
        read = readline("minishell : ");
    envp(env, en);
    *list = parce(read, *en);
    while (*list == NULL || ft_strcmp(read, "") == 0)
    {
        read = readline("minishell : ");
        add_history(read);
        *list = parce(read, *en);
    }
}

int	main(int arc, char **arv, char **env)
{
	struct sigaction	sa;
    char	*read;
    char **list = NULL;
    t_data *data;
    t_node *en = NULL;
    t_command_line *cmd = NULL;
    t_pipes pipes;

    arv = NULL;
    arc = 0;
	sa.sa_sigaction = &sigintHandler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
    while (1)
	{
        read = readline("minishell : ");
		if (read == NULL)
 			exit(1);
        add_history(read);
        prompt(read, &en, env, &list);
        data = malloc(sizeof(t_data));
        init(&data, list, &cmd);
        init_pipes(&pipes, data);
        push(&data, list, &pipes);
        if (!data->error)
		    ft_pipes(&pipes, &data, &en);
        // int k = 0;
        // while (k < (*data).pi)
        // {
        //     printf("COMMAND: %s\n", data->commands[k].command);
        //     int j = -1;
        //     while (data->commands[k].arguments[++j])
        //         printf("ARG: %s\n", data->commands[k].arguments[j]);
        //     j = -1;
        //     while (data->commands[k].here_doc[++j])
        //         printf("HEDOC: %s\n", data->commands[k].here_doc[j]);
        //     if (data->commands[k].std_in > 0)
        //         printf("STD_IN: %d\n", data->commands[k].std_in);
        //     if (data->commands[k].std_out > 0)
        //         printf("STD_OUT: %d\n", data->commands[k].std_out);
        //     k++;
        // }
    }
}