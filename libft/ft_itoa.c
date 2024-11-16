/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmendes <nmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:35:48 by nmendes           #+#    #+#             */
/*   Updated: 2024/05/18 17:09:52 by nmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				i;
	unsigned int	num;

	i = num_size(n);
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		num = (unsigned int)(n * -1);
	}
	else
		num = (unsigned int)n;
	if (n == 0)
		s[0] = '0';
	s[i] = '\0';
	while (num != 0)
	{
		s[i - 1] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (s);
}
