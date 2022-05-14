/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:53:34 by mmounib           #+#    #+#             */
/*   Updated: 2022/05/12 14:06:04 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_char(t_node *en)
{
	int len;
	int i;
	char **env;
	t_node *ptr;

	len = 1;
	i = 0;
	ptr = en;
	while (en)
	{
		len++;
		en = (en)->next;
	}
	env = malloc(sizeof(char *) * len);
	while (ptr)
	{
		env[i++] = ft_strjoin(ft_chrjoin(ptr->name, ptr->egal), ptr->path);
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

