/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:25:29 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 13:12:03 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_data *data, int k)
{
	char	*cwd;

	if (chdir("./") != 0)
		return ;
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			printf("minishell: %s\n", strerror(errno));
			return ;
		}
		write(data->commands[k].std_out, cwd, ft_strlen(cwd));
		write(data->commands[k].std_out, "\n", 1);
		free(cwd);
	}
	return ;
}
