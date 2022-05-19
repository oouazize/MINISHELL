/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:14:16 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 16:27:32 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_switch(char **list)
{
	int i = 0;
	int j;
	char *ptr1;
	char *ptr2;
	int flag = 0;
	int x = 0;
	while (list[i])
	{
		if (flag == 0 && (ft_strcmp(list[i], ">") == 0 || ft_strcmp(list[i], "<") == 0 || ft_strcmp(list[i], ">>") == 0))
		{
			x = 1;
			j = i;
			flag = 1;
		}
		else if (ft_strcmp(list[i], "<<") == 0 && x)
		{
			x = 0;
			ptr1 = list[i];
			ptr2 = list[i + 1];
			while (i > j)
			{
				list[i + 1] = list[i - 1];
				i--;
			}
			list[i] = ptr1;
			list[i + 1] = ptr2;
			j = i + 1;
			i = - 1;
			flag = 0;
		}
		i++;
	}
}

void	ft_switch2(char **list)
{
	int i = 0;
	int j = 0;
	char *ptr;
	char *ptr2;
	while (list[i])
	{
		if (ft_strcmp(list[i], ">") && ft_strcmp(list[i], "<") && ft_strcmp(list[i], ">>") && ft_strcmp(list[i], "<<") && ft_strcmp(list[i - 1], ">") && ft_strcmp(list[i - 1], "<") && ft_strcmp(list[i - 1], ">>") && ft_strcmp(list[i - 1], "<<"))
		{
			ptr = list[i];
			while (i > 0)
			{
				list[i] = list[i - 1];
				i--;
			}
			list[0] = ptr;
			break;
		}
		i++;
	}
}

char	**parce(char *read, t_node *en)
{
	int flag = 0;
	char *line = change_line(read);
	if (!line)
		return (0);
	char **list = ft_split(line, 32);
	list = rechange(list);
	int i = -1;
	while (list[++i])
	{
		if (i && !ft_strcmp(list[i - 1], "<<"))
			flag = 1;
		list[i] = edit_quote(list[i], en, flag);
		if (!list[i])
			return (0);
	}
	ft_switch(list);
	if (ft_strcmp(list[0], ">") == 0 || ft_strcmp(list[0], "<") == 0 || ft_strcmp(list[0], ">>") == 0 || ft_strcmp(list[0], "<<") == 0)
		ft_switch2(list);
	return (list);
}