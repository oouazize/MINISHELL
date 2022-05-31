/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:14:16 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/30 20:55:43 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quote(char *list)
{
	int	i;

	i = -1;
	while (list[++i])
	{
		if (list[i] == 34)
		{
			while (list[++i] && list[i] != 34)
			{
			}
			if (list[i] != 34)
				return (1);
		}
		else if (list[i] == 39)
		{
			while (list[++i] && list[i] != 39)
			{
			}
			if (list[i] != 39)
				return (1);
		}
	}
	return (0);
}

void	ft_switch2(char **list)
{
	int		i;
	int		j;
	char	*ptr;
	char	*ptr2;

	i = -1;
	j = 0;
	while (list[++i])
	{
		if (ft_strcmp(list[i], ">") && ft_strcmp(list[i], "<")
			&& ft_strcmp(list[i], ">>") && ft_strcmp(list[i], "<<")
			&& ft_strcmp(list[i - 1], ">") && ft_strcmp(list[i - 1], "<")
			&& ft_strcmp(list[i - 1], ">>") && ft_strcmp(list[i - 1], "<<"))
		{
			ptr = list[i];
			while (i > 0)
			{
				list[i] = list[i - 1];
				i--;
			}
			list[0] = ptr;
			break ;
		}
	}
}

int	norm_parce(char **list, t_node *en, int i)
{
	char	*lineii;
	int		flag;

	flag = 0;
	if (i && !ft_strcmp(list[i - 1], "<<"))
		flag = 1;
	if (check_quote(list[i]))
	{
		printf("Error!!, Unclosed Quote!\n");
		return (1);
	}
	lineii = list[i];
	list[i] = edit_quote(list[i], en, flag, -1);
	free(lineii);
	if (!list[i])
		return (1);
	return (0);
}

char	**parce(char *read, t_node *en)
{
	char	**list;
	char	*line;
	int		i;

	i = -1;
	line = change_line(read);
	if (ft_strcmp(line, "") == 0)
		return (0);
	list = ft_split(line, 32);
	free(line);
	list = rechange(list);
	while (list[++i])
	{
		if (norm_parce(list, en, i))
		{
			free_spl(list);
			return (0);
		}
	}
	if (ft_strcmp(list[0], ">") == 0
		|| ft_strcmp(list[0], "<") == 0 || ft_strcmp(list[0], ">>") == 0
		|| ft_strcmp(list[0], "<<") == 0)
		ft_switch2(list);
	return (list);
}
