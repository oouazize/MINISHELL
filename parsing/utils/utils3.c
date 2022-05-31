/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:48:52 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/31 13:37:17 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	ft_min_n(char *str, int len, int n)
{
	unsigned int	min_n;

	min_n = n;
	min_n *= -1;
	str[0] = '-';
	while (min_n)
	{
		str[len--] = (min_n % 10) + 48;
		min_n /= 10;
	}
	return (*str);
}

char	n_positive(char	*str, int len, int n)
{
	if (n == 0)
		str[len] = n + 48;
	if (n == -2147483648)
	{
		ft_min_n(str, len, n);
		return (*str);
	}
	else if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n)
	{
		str[len--] = (n % 10) + 48;
		n /= 10;
	}
	return (*str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		n_len;
	int		len;

	i = 0;
	len = 0;
	n_len = n;
	while (n_len)
	{
		n_len /= 10;
		len++;
	}
	if (n == 0)
		len++;
	if (n < 0)
		len += 1;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len--] = '\0';
	n_positive(str, len, n);
	return (str);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*src;

	i = 0;
	if (!s)
		return (-1);
	src = (char *)s;
	while (src[i])
	{
		if (src[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}
