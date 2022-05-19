/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:09:29 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 16:39:01 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void red2(t_data **data, char **list, int *i, int k)
{
    if (ft_strcmp(list[*i], ">") == 0)
            (*data)->fd_out = open(list[++(*i)], O_CREAT | O_RDWR | O_TRUNC, 0777);
    else if (ft_strcmp(list[*i], ">>") == 0)
        (*data)->fd_out = open(list[++(*i)], O_CREAT | O_RDWR | O_APPEND, 0777);
    (*data)->f_out[k]--;
    if ((*data)->fd_out < 0)
    {
        printf("minishell: %s: %s\n", list[*i], strerror(errno));
        (*data)->error = 1;
        exit_status = 1;
    }
    (*data)->commands[k].std_out = (*data)->fd_out;
    if ((*data)->f_out[k])
        close((*data)->fd_out);
}
    
int redirection(t_data **data, char **list, int *i, int k)
{
    if (list[*i + 1] == NULL)
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        (*data)->error = 1;
        exit_status = 258;
        return (0);
    }
    else if (!ft_strcmp(list[*i + 1], "|"))
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        (*data)->error = 1;
        exit_status = 258;
        return (0);
    }
    if (!ft_strcmp(list[*i], ">") || !ft_strcmp(list[*i], ">>"))
        red2(data, list, i, k);
    else
    {
        (*data)->fd_in = open(list[++(*i)], O_RDONLY, 0777);
        (*data)->f_in--;
        if ((*data)->fd_in < 0)
        {
            printf("minishell: %s: %s\n", list[*i], strerror(errno));
            exit_status = 1;
            (*data)->error = 1;
           return (2);
        }
        (*data)->commands[k].std_in = (*data)->fd_in;
        if ((*data)->f_in)
            close((*data)->fd_in);
    }
    return (0);
}

void    ft_here_doc(t_data **data, int k, int *her)
{
    char *join;
    char *line;

    line = readline("> ");
    join = ft_strjoin((*data)->commands[k].here_doc[--(*her)], "\n");
    while (line)
    {
		line = ft_strjoin(line, "\n");
        if (ft_strcmp(line, join) == 0)
        {
            join = ft_strjoin((*data)->commands[k].here_doc[++(*her)], "\n");
            if (ft_strcmp(join, "\n") == 0)
                break ;
        }
    	write((*data)->commands[k].std_in, line, ft_strlen(line));
        free(line);
        line = readline("> ");
    }
	
}

char *non_printable(char *line)
{
    int i;
    int j;
    char *ptr;

    ptr = malloc(sizeof(char) * ft_strlen(line));
    i = -1;
    j = 0;
    while (line[++i])
    {
        if (line[i] != 1)
            ptr[j++] = line[i];
    }
    ptr[j] = '\0';
    return (ptr);
}

void    push(t_data **data, char **list, t_pipes *pipes)
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
            if (ft_strcmp(list[i], ">") == 0 || ft_strcmp(list[i], ">>") == 0 || ft_strcmp(list[i], "<") == 0)
            {
                if (redirection(data, list, &i, k) == 2)
                    return ;
            }
            else if (ft_strcmp(list[i], "<<") == 0)
            {
                if (list[i + 1] == NULL)
                {
                    printf("minishell: syntax error near unexpected token `newline'\n");
                    (*data)->error = 1;
                    exit_status = 258;
                    return ;
                }
                else if (!ft_strcmp(list[i + 1], "|"))
                {
                    printf("minishell: syntax error near unexpected token `|'\n");
                    (*data)->error = 1;
                    exit_status = 258;
                    return ;
                }
                (*data)->commands[k].here_doc[her++] = list[++i];
                // pipe(pipes->pipefd[k]);
                //pipe fd_pipe
                (*data)->tmp_fd = open("/tmp/tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
				(*data)->commands[k].std_in = (*data)->tmp_fd;
                ft_here_doc(data, k, &her);
				// close(pipes->pipefd[k][1]);
				(*data)->tmp_fd = open("/tmp/tmp", O_CREAT | O_RDWR, 0777);
				(*data)->commands[k].std_in = (*data)->tmp_fd;
            }
            else if (i == (*data)->arr[ar])
                (*data)->commands[k].command = non_printable(list[i]);
            else
                (*data)->commands[k].arguments[arg++] = non_printable(list[i]);
        }
        j++;
        ar++;
        k++;
    }
    return ;
}