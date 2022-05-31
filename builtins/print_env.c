/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:54:17 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/29 13:11:59 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_data *data, t_node *en, int k)
{
	while (en)
	{
		if (en->egal != '+')
		{
			write(data->commands[k].std_out, en->name, ft_strlen(en->name));
			write(data->commands[k].std_out, &en->egal, 1);
			write(data->commands[k].std_out, en->path, ft_strlen(en->path));
			write(data->commands[k].std_out, "\n", 1);
		}
		en = en->next;
	}
}
