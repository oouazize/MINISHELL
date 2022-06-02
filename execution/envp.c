/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:37:27 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 23:51:31 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envp(char **env, t_node **en)
{
	t_node	*new;
	int		i;
	int		size;

	i = -1;
	if (*en)
		i = 0;
	if (i == -1)
	{
		i++;
		while (env[i])
			i++;
		size = i;
		i = 0;
		while (size-- > 0)
		{
			new = ft_lstnew(env[i++], 0);
			ft_lstadd_back(en, new);
		}
	}
}
