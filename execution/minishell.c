/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:14:46 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/30 10:51:57 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell1.h"

char	*get_path_env(t_node *env)
{
	while (env->name)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			return (env->path);
		if (!env->next)
			break ;
		env = env->next;
	}
	return (0);
}

int	ft_path2(char *cwd, char ***paths)
{
	if (!ft_strcmp(cwd, "/bin"))
		*paths = ft_split(cwd, ':');
	else
		return (1);
	return (0);
}

char	*ft_path(t_node *envs, char *command, t_data **data, char *cwd)
{
	char	*pure_paths;
	char	**paths;
	char	*join;
	int		i;

	i = 0;
	pure_paths = get_path_env(envs);
	if (pure_paths)
		paths = ft_split(pure_paths, ':');
	else if (!pure_paths && !ft_strstr(command, "/bin/"))
	{
		if (ft_path2(cwd, &paths))
			return ("NO");
	}
	else
		return (command);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], ft_strdup("/"));
		join = ft_strjoin(paths[i], ft_strdup(command));
		if (access(join, X_OK) == 0)
			return (join);
		i++;
	}
	return (command);
}
