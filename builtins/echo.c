/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:10 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 18:10:35 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_data *list, int flag, int k, int *i)
{
	if (flag)
	{
		write(list->commands[k].std_out, list->commands[k].arguments[*i],
			ft_strlen(list->commands[k].arguments[*i]));
		if (list->commands[k].arguments[*i + 1] != NULL)
			write(list->commands[k].std_out, " ", 1);
	}
	else
	{
		write(list->commands[k].std_out, list->commands[k].arguments[*i],
			ft_strlen(list->commands[k].arguments[*i]));
		if (list->commands[k].arguments[*i + 1] == NULL)
			write(list->commands[k].std_out, "\n", 1);
		else
			write(list->commands[k].std_out, " ", 1);
	}
	(*i)++;
}

int	ft_cmpecho(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (1);
	if (s[++i] != '-')
	{
		return (0);
	}
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	if (i == 1)
		return (0);
	return (1);
}

void	echo(t_data *list, int k, int flag)
{
	int	i;
	int	parram;

	i = 0;
	parram = 0;
	if (!list->commands[k].arguments[0])
		printf("\n");
	if (!parram && ft_cmpecho(list->commands[k].arguments[i]))
	{
		i++;
		flag = 1;
		if (!list->commands[k].arguments[i])
			return ;
		while (ft_cmpecho(list->commands[k].arguments[i]))
		{
			i++;
			if (!list->commands[k].arguments[i])
				return ;
		}
		parram = 1;
	}
	while (list->commands[k].arguments[i])
		print_echo(list, flag, k, &i);
}
