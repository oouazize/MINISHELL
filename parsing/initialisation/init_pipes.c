/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:48:21 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/18 15:03:49 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_pipes(t_pipes *pipes, t_data *data)
{
	pipes->in = 0;
	pipes->out = 0;
    pipes->pipefd = malloc(sizeof(int *) * (data->number_of_commands));
	if (!pipes->pipefd)
		return ;
	pipes->pid = malloc(sizeof(int) * data->number_of_commands);
}