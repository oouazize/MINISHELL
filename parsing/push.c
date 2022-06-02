/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:09:29 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 20:01:03 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*non_printable(char *line)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = malloc(sizeof(char) * ft_strlen(line) + 1);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] != 1)
			ptr[j++] = line[i];
	}
	ptr[j] = '\0';
	return (ptr);
}

int	ifat(t_data **data, char **list, int i)
{
	if (!(*data)->error && !(*data)->commands[(*data)->k].command
		&& !(*data)->commands[(*data)->k].here_doc[0]
		&& !(*data)->commands[(*data)->k].std_in
		&& ((*data)->commands[(*data)->k].std_out) == 1)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", list[i]);
		(*data)->error = 1;
		g_manager.exit_status = 258;
		return (1);
	}
	(*data)->index++;
	((*data)->k)++;
	(*data)->ar++;
	return (0);
}

int	push2(t_data **data, char **list, int *i)
{
	if (!ft_strcmp(list[*i], ">") || !ft_strcmp(list[*i], ">>")
		|| !ft_strcmp(list[*i], "<"))
	{
		if (redirection(data, list, i) == 2)
			return (1);
	}
	else
	{
		if (herdoc(data, list, i))
			return (1);
	}
	return (0);
}

void	push(t_data **data, char **list, int i)
{
	g_manager.exit_status = 0;
	while ((*data)->index < (*data)->number_of_commands
		&& g_manager.exit_status != 130)
	{
		(*data)->arg = 0;
		(*data)->her = 0;
		while (list[++i] && ft_strcmp(list[i], "|")
			&& g_manager.exit_status != 130)
		{
			if (!ft_strcmp(list[i], ">") || !ft_strcmp(list[i], ">>")
				|| !ft_strcmp(list[i], "<") || !ft_strcmp(list[i], "<<"))
			{
				if (push2(data, list, &i))
					return ;
			}
			else if (i == (*data)->arr[(*data)->ar])
				(*data)->commands[(*data)->k].command = non_printable(list[i]);
			else
				(*data)->commands[(*data)->k].arguments[(*data)->arg++]
					= non_printable(list[i]);
		}
		if (ifat(data, list, i))
			return ;
	}
}
