/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:53:31 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/18 14:46:17 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int counter(char **list, int flag)
{
    int i;
    int count;

    count = 0;
    i = 0;
    if (flag == 1)
    {
        while(list[++i])
        {
            if (ft_strcmp(list[i], "<") && ft_strcmp(list[i], ">") && ft_strcmp(list[i], "|"))
                count++;
        }
    }
    else if (flag == 2)
    {
        while(list[++i])
        {
            if (ft_strcmp(list[i], ">") == 0)
                count+=2;
        }
    }
    else if (flag == 3)
    {
        while(list[++i])
        {
            if (ft_strcmp(list[i], "<") == 0)
                    count+=2;
        }
    }
    else if (flag == 4)
    {
        while(list[++i])
        {
            if (ft_strcmp(list[i], "<<") == 0)
                    count+=2;
        }
    }
    return (count);
}

void    init_struct2(t_command_line **line, t_data **data, char **list)
{
    int i;
    int j;

    i = -1;
    *line = malloc(sizeof(t_command_line) * (*data)->pi);
    (*data)->commands = *line;
    (*data)->number_of_commands = (*data)->pi;
    while (++i < (*data)->pi)
    {
        (*data)->commands[i].command = malloc(sizeof(char) * (*data)->number_of_commands);
        (*data)->commands[i].command = 0;
        j = 0;
        (*data)->commands[i].arguments = malloc(sizeof(char *) * (counter(list, 1) + 1));
        while (j < counter(list, 1) + 1)
            (*data)->commands[i].arguments[j++] = NULL;
        j = 0;
        (*data)->commands[i].here_doc = malloc(sizeof(char *) * (counter(list, 4) + 1));
        while (j < counter(list, 4) + 1)
            (*data)->commands[i].here_doc[j++] = NULL;
        (*data)->tmp_fd = 0;
        (*data)->error = 0;
		(*data)->commands[i].std_in = 0;
        (*data)->commands[i].std_out = 1;
    }
}

void    init(t_data **data, char **list, t_command_line **line)
{
    int i;
    int x;
    int num;
    int j;

    j = 0;
    x = 0;
    i = -1;
    num = 0;
    (*data)->mark = 0;
    (*data)->pi = 1;
    while (list[++i])
    {
        if (ft_strcmp(list[i], "|") == 0)
            (*data)->pi++;
    }
    (*data)->index = 0;
    (*data)->f_out = malloc(sizeof(int) * (*data)->pi);
    (*data)->f_in = 0;
    (*data)->fd_in = 0;
    (*data)->fd_out = 0;
    init_struct2(line, data, list);
    (*data)->arr = malloc(sizeof(int) * (*data)->pi);
    if (ft_strcmp(list[0], ">") && ft_strcmp(list[0], "<"))
        (*data)->arr[j++] = 0;
    i = -1;
    while (list[++i])
    {
        if (ft_strcmp(list[i], "|") == 0)
        {
            (*data)->arr[j++] = i + 1;
            (*data)->mark = 1;
        }
        if (ft_strcmp(list[i], ">") == 0 || ft_strcmp(list[i], ">>") == 0)
        {
            if ((*data)->mark)
            {
                x++;
                num = 0;
            }
            (*data)->f_out[x] = ++num;
            (*data)->mark = 0;
        }
        if (ft_strcmp(list[i], "<") == 0)
            (*data)->f_in++;
    }
}