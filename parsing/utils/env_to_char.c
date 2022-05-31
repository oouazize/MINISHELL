/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:53:34 by mmounib           #+#    #+#             */
/*   Updated: 2022/05/31 13:31:55 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_long_max(unsigned long long int value, int s, const char *str)
{
	if (value > 9223372036854775807
		|| (s == -1 && value > 9223372036854775808ULL))
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		exit(255);
	}
}

long long int	ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	value;
	int						s;

	i = 0;
	value = 0;
	s = 1;
	while ((str[i] && str[i] >= 9 && str[i] <= 13)
		|| str[i] == 32)
		i++;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			s *= -1;
		if (str[i + 1] == '-' || str[i + 1] == '+')
			s = 0;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		value = (value * 10) + str[i++] - '0';
		ft_long_max(value, s, str);
	}
	return ((s * value) % 256);
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
	int		len;
	int		i;
	char	**env;
	t_node	*ptr;

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
		if (!ft_strcmp(ptr->path, ""))
			env[i++] = ft_chrjoin(ptr->name, ptr->egal);
		else
			env[i++] = ft_strjoin(ft_chrjoin(ptr->name, ptr->egal), ptr->path);
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}
