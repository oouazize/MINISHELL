/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:09:29 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/13 14:45:11 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void red2(t_data **data, char **list, int *i, int k)
{
    if (ft_strcmp(list[*i], ">") == 0)
        (*data)->fd_out = open(list[++(*i)], O_CREAT | O_RDWR | O_TRUNC, 0777);
    else if (ft_strcmp(list[*i], ">>") == 0)
        (*data)->fd_out = open(list[++(*i)], O_CREAT | O_RDWR | O_APPEND, 0777);
    (*data)->f_out--;
    if ((*data)->fd_out < 0)
    {
        printf("my shell: %s: %s\n", list[*i], strerror(errno));
        exit_status = 1;
    }
    (*data)->commands[k].std_out = (*data)->fd_out;
    (*data)->commands[k].out = list[*i];
    if ((*data)->f_out)
        close((*data)->fd_out);
}
    
void    redirection(t_data **data, char **list, int *i, int k)
{
    if (ft_strcmp(list[*i], ">") || ft_strcmp(list[*i], ">>"))
        red2(data, list, i, k);
    else
    {
        (*data)->fd_in = open(list[++(*i)], O_RDONLY, 0777);
        (*data)->f_in--;
        if ((*data)->fd_in < 0)
        {
            printf("my shell: %s: %s\n", list[*i], strerror(errno));
            exit_status = 1;
        }
        (*data)->commands[k].std_in = (*data)->fd_in;
        (*data)->commands[k].in = list[*i];
        if ((*data)->f_in)
            close((*data)->fd_in);
    }
}

void    push(t_data **data, char **list)
{
    int i;
	i = 0;
    int j = 0;
    int k = 0;
    int arg;
    int her;
    i = -1;
    j = (*data)->index;
    int ar = 0;
    while (j < (*data)->number_of_commands)
    {
        arg = 0;
        her = 0;
        while (list[++i] && ft_strcmp(list[i], "|"))
        {
            if (i == (*data)->arr[ar])
                (*data)->commands[k].command = list[i];
            else if (ft_strcmp(list[i], ">") == 0 || ft_strcmp(list[i], ">>") == 0 || ft_strcmp(list[i], "<") == 0)
                redirection(data, list, &i, k);
            else if (ft_strcmp(list[i], "<<") == 0)
                (*data)->commands[k].here_doc[her++] = list[++i];
            else
                (*data)->commands[k].arguments[arg++] = list[i];
        }
        j++;
        ar++;
        k++;
    }
}