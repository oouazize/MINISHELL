/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:31:26 by mmounib           #+#    #+#             */
/*   Updated: 2022/05/11 13:28:44 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell1.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
