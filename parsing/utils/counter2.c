/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:15:43 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 16:48:26 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add(void)
{
	char	*line;
	char	*line1;

	g_manager.f_status = 1;
	g_manager.fd_file = open("/tmp/temp1", O_CREAT | O_RDWR | O_APPEND, 0777);
	line = get_next_line(g_manager.fd_file);
	while (line)
	{
		line1 = line;
		line = ft_strtrim(line, "\n");
		add_history(line);
		free(line1);
		free(line);
		line = get_next_line(g_manager.fd_file);
	}
}

void	flag12(char **list, int flag, int *count)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		while (list[++(i)])
		{
			if (ft_strcmp(list[i], "<") && ft_strcmp(list[i], ">")
				&& ft_strcmp(list[i], "|"))
				(*count)++;
		}
	}
	else
	{
		while (list[++(i)])
		{
			if (ft_strcmp(list[i], ">") == 0)
				(*count)++;
		}
	}
}

void	flag34(char **list, int flag, int *count)
{
	int	i;

	i = -1;
	if (flag == 3)
	{
		while (list[++(i)])
		{
			if (ft_strcmp(list[i], "<") == 0)
				(*count)++;
		}
	}
	else
	{
		while (list[++(i)])
		{
			if (ft_strcmp(list[i], "<<") == 0)
				(*count)++;
		}
	}
}

int	counter2(char **list, int flag)
{
	int	count;

	count = 0;
	if (flag == 1 || flag == 2)
		flag12(list, flag, &count);
	else if (flag == 3 || flag == 4)
		flag34(list, flag, &count);
	return (count);
}
