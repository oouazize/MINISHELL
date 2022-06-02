/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:14:14 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 19:57:45 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*edit_quote(char *line, t_node *en, int flag, int i)
{
	int		retur;
	char	*str;

	str = ft_strdup("");
	while (line[++i])
	{
		if (line[i] == 39)
		{
			if (single_q(line, &str, &i))
				return (0);
		}
		else if (line[i] == 34 || line[i] == '$')
		{
			if (flag)
				retur = non_dollar(line, &str, &i);
			else
				retur = double_q(line, &str, &i, en);
			if (retur == 2)
				i--;
		}
		else
			str = ft_chrjoin(str, line[i]);
	}
	return (str);
}
