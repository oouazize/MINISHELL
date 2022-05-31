/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:02:16 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 21:40:14 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_spl(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list[i]);
	free(list);
}

void	free_str(t_command_line *c)
{
	free(c->command);
	free_spl(c->arguments);
	if (c->here_doc != NULL)
		free_spl(c->here_doc);
}

void	free_data(t_data **g)
{
	int	i;

	i = 0;
	while (i < (*g)->pi)
	{
		free_str(&(*g)->commands[i]);
		i++;
	}
	free(&(*g)->commands[0]);
	free((*g)->f_out);
	free((*g)->arr);
	free(*g);
}

void	ft_free_all(t_data **data, t_pipes *pipes, t_exp *exp, char **list)
{
	free(pipes->pipefd);
	free(pipes->pid);
	free_data(data);
}
