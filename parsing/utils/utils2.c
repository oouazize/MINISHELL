/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:47:16 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/19 15:27:35 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return ;
}

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
	return ;
}

t_node	*ft_lstnew(char *data, t_node **en, int flag)
{
	t_node	*new;
	int i=-1;
	char *name = ft_strdup("");
	char *path = ft_strdup("");

	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	while (data[++i] && data[i] != '=' && data[i] != '+')
		name = ft_chrjoin(name, data[i]);
	if (data[i] == '+')
	{
		if (data[i + 1] != '=')
			exit (0);
		else
			i++;
	}
	while (data[++i])
		path = ft_chrjoin(path, data[i]);
	new->name = name;
	if (flag)
		new->egal = '+';
	else
		new->egal = '=';
	new->path = path;
	new->next = NULL;
	return (new);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*first;
	unsigned char	*second;

	i = 0;
	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (first[i] && second[i] && first[i] == second[i])
		i++;
	return (first[i] - second[i]);
}

char	*ft_chrjoin(char *s1, char c)
{
	int		i;
	int		j;
	char	*string;
	int		len;

	i = -1;
	j = 0;
	if (!s1)
	{
		char *s = malloc(sizeof(char) * 2);
		s[0] = c;
		s[1]= '\0';
		return (s);
	}
	len = ft_strlen(s1);
	string = (char *)malloc((len + 2) * sizeof(char));
	if (string == NULL)
		return (0);
	while (s1[++i])
		string[i] = s1[i];
	string [i++] = c;
	string[i] = '\0';
	free(s1);
	return (string);
}