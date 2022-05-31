/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:53:31 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 22:04:59 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	counter_pipe(char **list, t_data **data)
{
	int	i;

	i = -1;
	(*data)->pi = 1;
	while (list[++i])
	{
		if (ft_strcmp(list[i], "|") == 0)
			(*data)->pi++;
	}
}

void	init_list(t_command_line **line, t_data **data, char **list)
{
	int	i;
	int	j;

	i = -1;
	*line = malloc(sizeof(t_command_line) * (*data)->pi);
	(*data)->commands = *line;
	while (++i < (*data)->pi)
	{
		(*data)->commands[i].command = NULL;
		j = 0;
		(*data)->commands[i].arguments
			= malloc(sizeof(char *) * (counter2(list, 1) + 1));
		while (j < counter2(list, 1) + 1)
			(*data)->commands[i].arguments[j++] = NULL;
		j = 0;
		(*data)->commands[i].here_doc
			= malloc(sizeof(char *) * (counter2(list, 4) + 1));
		while (j < counter2(list, 4) + 1)
			(*data)->commands[i].here_doc[j++] = NULL;
		(*data)->commands[i].std_in = 0;
		(*data)->commands[i].std_out = 1;
	}
}

void	init_data2(t_data **data, char **list, int x, int num)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (list[++i])
	{
		if (ft_strcmp(list[i], "|") == 0)
		{
			(*data)->arr[j++] = i + 1;
			x++;
			num = 0;
		}
		if (ft_strcmp(list[i], ">") == 0 || ft_strcmp(list[i], ">>") == 0)
			(*data)->f_out[x] = ++num;
		if (ft_strcmp(list[i], "<") == 0)
			(*data)->f_in++;
	}
}

void	init_data(t_data **data, char **list)
{
	int	i;

	i = 0;
	counter_pipe(list, data);
	(*data)->number_of_commands = (*data)->pi;
	(*data)->f_in = 0;
	(*data)->f_out = malloc(sizeof(int) * (*data)->pi);
	while (i < (*data)->pi)
		(*data)->f_out[i++] = 0;
	(*data)->arr = malloc(sizeof(int) * (*data)->pi);
	if (ft_strcmp(list[0], ">") && ft_strcmp(list[0], "<"))
		(*data)->arr[0] = 0;
	(*data)->fd_in = 0;
	(*data)->fd_out = 0;
	(*data)->tmp_fd = 0;
	(*data)->error = 0;
	(*data)->index = 0;
	(*data)->ar = 0;
	(*data)->k = 0;
	(*data)->nb_her = 0;
	init_data2(data, list, 0, 0);
}

void	init(t_data **data, char **list, t_command_line **line)
{
	init_data(data, list);
	init_list(line, data, list);
}
