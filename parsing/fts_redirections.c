/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:57:04 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 23:49:10 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	red2(t_data **data, char **list, int *i)
{
	if (ft_strcmp(list[*i], ">") == 0)
		(*data)->fd_out = open(list[++(*i)], O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (ft_strcmp(list[*i], ">>") == 0)
		(*data)->fd_out = open(list[++(*i)], O_CREAT | O_RDWR | O_APPEND, 0777);
	(*data)->f_out[(*data)->k]--;
	if ((*data)->fd_out < 0)
	{
		printf("minishell: %s: %s\n", list[*i], strerror(errno));
		(*data)->error = 1;
		g_manager.exit_status = 1;
	}
	(*data)->commands[(*data)->k].std_out = (*data)->fd_out;
	if ((*data)->f_out[(*data)->k])
		close((*data)->fd_out);
}

int	redirection(t_data **data, char **list, int *i)
{
	if (error_redirection(data, list, i))
		return (2);
	if (!ft_strcmp(list[*i], ">") || !ft_strcmp(list[*i], ">>"))
		red2(data, list, i);
	else
	{
		(*data)->fd_in = open(list[++(*i)], O_RDONLY, 0777);
		(*data)->f_in--;
		if ((*data)->fd_in < 0)
		{
			printf("minishell: %s: %s\n", list[*i], strerror(errno));
			g_manager.exit_status = 1;
			(*data)->error = 1;
			return (2);
		}
		(*data)->commands[(*data)->k].std_in = (*data)->fd_in;
		if ((*data)->f_in)
			close((*data)->fd_in);
	}
	return (0);
}

void	ft_here2(t_data **data, int *her, char *line)
{
	char	*join;

	join = ft_strjoin((*data)->commands[(*data)->k].here_doc[*her],
			ft_strdup("\n"));
	while (line)
	{
		line = ft_strjoin(line, ft_strdup("\n"));
		if (ft_strcmp(line, join) == 0)
		{
			join = ft_strjoin((*data)->commands[(*data)->k].here_doc[++(*her)],
					ft_strdup("\n"));
			if (ft_strcmp(join, "\n") == 0)
				break ;
		}
		write((*data)->commands[(*data)->k].std_in, line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
}

void	ft_here_doc(t_data **data)
{
	char	*line;
	int		pid;

	g_manager.flag_sig = 1;
	pid = fork();
	if (pid)
		g_manager.flag_sig = -1;
	if (pid == 0)
	{
		line = readline("> ");
		ft_here2(data, &(*data)->her, line);
		exit(0);
	}
	waitpid(pid, &g_manager.exit_status, 0);
	g_manager.exit_status /= 256;
	g_manager.flag_sig = 0;
}

int	herdoc(t_data **data, char **list, int *i)
{
	if (error_redirection(data, list, i))
		return (1);
	(*data)->commands[(*data)->k]
		.here_doc[(*data)->her] = ft_strdup(list[++(*i)]);
	(*data)->tmp_fd = open("/tmp/tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
	(*data)->commands[(*data)->k].std_in = (*data)->tmp_fd;
	ft_here_doc(data);
	(*data)->tmp_fd = open("/tmp/tmp", O_CREAT | O_RDWR, 0777);
	(*data)->commands[(*data)->k].std_in = (*data)->tmp_fd;
	(*data)->her++;
	return (0);
}
