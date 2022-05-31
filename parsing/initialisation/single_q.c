/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:06:04 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 22:52:20 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	single_q(char *line, char **str, int *i)
{
	int	len;
	int	start;
	int	flag;

	len = 0;
	flag = 0;
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != 39)
	{
		if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
			flag = 1;
		len++;
		(*i)++;
	}
	if (!line[*i])
	{
		printf("ERROR!\n");
		return (1);
	}
	*str = ft_strjoin(*str, ft_substr(line, start, len));
	if (flag)
		*str = ft_chrjoin(*str, 1);
	return (0);
}
