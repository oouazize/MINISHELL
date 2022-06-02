/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:03:10 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 20:12:55 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	siginthandler(int signum)
{
	g_manager.f_status = 0;
	if (signum == SIGINT && g_manager.flag_sig == 0)
	{
		g_manager.exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_manager.flag_sig != -1)
	{
		write(1, "\n", 1);
		g_manager.flag_sig = 0;
		g_manager.exit_status = 130;
		exit(130);
	}
	else
		g_manager.exit_status = 130;
}

int	last_etap2(char **list, char *read, int *j, int *i)
{
	if (read == NULL)
		exit(0);
	if (list == NULL)
		return (0);
	while (list[++(*i)])
	{
		if (!ft_strcmp(list[*i], ""))
			(*j)++;
	}
	return (1);
}

char	**last_etap(char **list, char *read, int i)
{
	int		j;
	char	**tab;

	j = 0;
	if (last_etap2(list, read, &j, &i) == 0)
		return (0);
	if (j == 0)
		return (list);
	tab = malloc(sizeof(char *) * i);
	i = -1;
	j = 0;
	while (list[++i])
	{
		if (ft_strcmp(list[i], "") || g_manager.dlr != 1)
			tab[j++] = ft_strdup(list[i]);
	}
	tab[j] = NULL;
	free_spl(list);
	if (tab[0] == NULL)
	{
		free(tab);
		return (0);
	}
	g_manager.dlr = 0;
	return (tab);
}

void	prompt(t_node **en, char **env, char ***list)
{
	char	*read;

	read = readline("minishell : ");
	if (read == NULL)
		exit(0);
	write(g_manager.fd_file, read, ft_strlen(read));
	write(g_manager.fd_file, "\n", 1);
	add_history(read);
	close(g_manager.fd_file);
	while (read != NULL && ft_strcmp(read, "") == 0)
		read = readline("minishell : ");
	envp(env, en);
	*list = parce(read, *en, -1);
	if (*list)
		*list = last_etap(*list, read, -1);
	while (*list == NULL || ft_strcmp(read, "") == 0)
	{
		if (read == NULL)
			exit(0);
		read = readline("minishell : ");
		add_history(read);
		*list = parce(read, *en, -1);
		*list = last_etap(*list, read, -1);
	}
	free(read);
}

int	main(int arc, char **list, char **env)
{
	t_node			*en;
	t_pipes			pipes;
	t_exp			exp;
	t_data			*data;
	t_command_line	*cmd;

	arc = 0;
	en = NULL;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_add();
		list = NULL;
		cmd = NULL;
		prompt(&en, env, &list);
		data = malloc(sizeof(t_data));
		init(&data, list, &cmd);
		init_pipes(&pipes, data, &exp, &en);
		push(&data, list, -1);
		free_spl(list);
		if (!data->error)
			ft_pipes(exp, &pipes, &data, &en);
		ft_free_all(&data, &pipes);
	}
}
