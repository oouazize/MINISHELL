/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:53:34 by mmounib           #+#    #+#             */
/*   Updated: 2022/05/18 17:19:08 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 1;
	i = ft_isspace(str);
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i + 1] == '-' || str[i + 1] == '+')
			sign = 0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (res > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (sign * res);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int d)
{
	if (d >= 48 && d <= 57)
		return (1);
	else
		return (0);
}

char	**env_to_char(t_node *en)
{
	int len;
	int i;
	char **env;
	t_node *ptr;

	len = 1;
	i = 0;
	ptr = en;
	while (en)
	{
		len++;
		en = (en)->next;
	}
	env = malloc(sizeof(char *) * len);
	while (ptr)
	{
		env[i++] = ft_strjoin(ft_chrjoin(ptr->name, ptr->egal), ptr->path);
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

