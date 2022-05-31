/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:23:50 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 18:19:37 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd2(t_data *list, t_node **en)
{
	char	*cwd;
	char	*str1;
	char	*str2;
	t_node	*ptr;

	ptr = *en;
	str1 = "cd: error retrieving current directory:";
	str2 = "getcwd: cannot access parent directories:";
	cwd = getcwd(NULL, 0);
	if (cwd == 0)
		printf("%s %s %s\n", str1, str2, strerror(errno));
	else
	{
		while (ptr)
		{
			if (!ft_strcmp(ptr->name, "PWD"))
			{
				free(ptr->path);
				ptr->path = ft_strdup(cwd);
			}
			ptr = ptr->next;
		}
	}
	free(cwd);
}

void	cd(t_data *list, t_node **en)
{
	int		i;
	char	*str;

	i = 1;
	if (!list->commands->arguments[0]
		|| ft_strcmp(list->commands->arguments[0], "~") == 0)
		chdir(get_env("HOME", *en));
	else if (list->commands->arguments[0][0] == '~'
		&& ft_strlen(list->commands->arguments[0]) > 2)
	{
		chdir(get_env("HOME", *en));
		while (list->commands->arguments[0][i] == '/')
			i++;
		str = ft_substr(list->commands->arguments[0], i,
				ft_strlen(list->commands->arguments[0]));
		if (chdir(str) != 0)
		{
			printf("minishell: cd: %s: %s\n",
				list->commands->arguments[0], strerror(errno));
			g_manager.exit_status = 1;
		}
		free(str);
	}
	else if (chdir(list->commands->arguments[0]) != 0)
	{
		printf("minishell: cd: %s: %s\n",
			list->commands->arguments[0], strerror(errno));
		g_manager.exit_status = 1;
	}
	cd2(list, en);
}
