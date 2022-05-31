/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:48:21 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 18:11:41 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exp(t_exp *exp, t_node **en)
{
	exp->i = -1;
	exp->p = 1;
	exp->egal = 0;
	exp->flag = 0;
	exp->path = 0;
	exp->name = 0;
	exp->env = en;
}

void	init_pipes(t_pipes *pipes, t_data *data, t_exp *exp, t_node **en)
{
	pipes->in = 0;
	pipes->out = 0;
	pipes->pipefd = malloc(sizeof(int *) * (data->number_of_commands));
	if (!pipes->pipefd)
		return ;
	pipes->pid = malloc(sizeof(int) * data->number_of_commands);
	if (!pipes->pid)
		return ;
	init_exp(exp, en);
}
