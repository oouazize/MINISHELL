/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:29:05 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/30 13:06:46 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read3934(char *read, int *i, char **line)
{
	if (read[*i] == 39)
	{
		*line = ft_chrjoin(*line, read[*i]);
		while (read[++(*i)] && read[*i] != 39)
			*line = ft_chrjoin(*line, read[*i]);
		*line = ft_chrjoin(*line, read[*i]);
	}
	else
	{
		*line = ft_chrjoin(*line, read[*i]);
		while (read[++(*i)] && read[*i] != 34)
			*line = ft_chrjoin(*line, read[*i]);
		*line = ft_chrjoin(*line, read[*i]);
	}
}

void	line39(char *line, int *i)
{
	(*i)++;
	while (line[*i] != 39 && line[*i] != '\0')
	{
		if (line[*i] == 32)
			line[*i] = -2;
		else if (line[*i] == 34)
			line[*i] = -5;
		else if (line[*i] == '<')
			line[*i] = -4;
		else if (line[*i] == '>')
			line[*i] = -7;
		else if (line[*i] == '|')
			line[*i] = -1;
		(*i)++;
	}
}

void	line34(char *line, int *i)
{
	(*i)++;
	while (line[*i] != 34 && line[*i] != '\0')
	{
		if (line[*i] == 32)
			line[*i] = -2;
		else if (line[*i] == 39)
			line[*i] = -6;
		else if (line[*i] == '<')
			line[*i] = -4;
		else if (line[*i] == '>')
			line[*i] = -7;
		else if (line[*i] == '|')
			line[*i] = -1;
		(*i)++;
	}
}

int	add_space(char *read, int *i, char **line)
{
	if (read[*i] == 39 || read[*i] == 34)
		read3934(read, i, line);
	else if (read[*i] != '<' && read[*i] != '>' && read[*i] != '|')
		*line = ft_chrjoin(*line, read[*i]);
	else if (read[*i] == read[(*i) + 1])
	{
		*line = ft_chrjoin(ft_chrjoin(*line, 32), read[*i]);
		*line = ft_chrjoin(ft_chrjoin(*line, read[(*i) + 1]), 32);
		(*i)++;
	}
	else if (read[*i] == '<' && read[(*i) + 1] == '>')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_manager.exit_status = 258;
		return (0);
	}
	else
	{
		if (*i && read[(*i) - 1] != 32)
			*line = ft_chrjoin(*line, 32);
		*line = ft_chrjoin(*line, read[*i]);
		if (read[(*i) + 1] != 32 && read[(*i) + 1])
			*line = ft_chrjoin(*line, 32);
	}
	return (1);
}

char	*change_line(char *read)
{
	int		i;
	char	*line;

	i = -1;
	line = ft_strdup("");
	while (read != NULL && read[++i])
	{
		if (add_space(read, &i, &line) == 0)
			return (NULL);
		if (!read[i])
			break ;
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == 39)
			line39(line, &i);
		if (line[i] == 34)
			line34(line, &i);
		if (!line[i])
			break ;
	}
	return (line);
}
