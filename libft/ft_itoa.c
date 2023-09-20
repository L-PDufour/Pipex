/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:34:13 by ldufour           #+#    #+#             */
/*   Updated: 2023/03/06 08:29:21 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenght(int n)
{
	int	len;
	int	x;

	len = 0;
	if (n <= 0)
		len++;
	x = n;
	while (x != 0)
	{
		x /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	b;

	b = n;
	len = ft_lenght(b);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (b == 0)
		*str = '0';
	if (b < 0)
	{
		b *= -1;
		str[0] = '-';
	}
	str[len] = '\0';
	while (b != 0)
	{
		str[--len] = (b % 10) + 48;
		b /= 10;
	}
	return (str);
}

// #include <stdio.h>
// #include <limits.h>
// int main()
// {
// 	char *a;
// 	a = ft_itoa(0000001);
// 	printf("%s", a);
// }

// char	*ft_itoa(int n)
// {
// 	char	*str;
// 	int		len;

// 	len = ft_lenght(n);
// 	str = (char *)malloc(sizeof(char) * len + 1);
// 	if (!str)
// 		return (NULL);
// 	str[len] = '\0';
// 	if (n == 0)
// 		*str = '0';
// 	if (n < 0)
// 	{
// 		str[0] = '-';
// 		while (n != 0)
// 		{
// 			str[--len] = 48 - (n % 10);
// 			n /= 10;
// 		}
// 	}
// 	else
// 	{
// 		while (n != 0)
// 		{
// 			str[--len] = (n % 10) + 48;
// 			n /= 10;
// 		}
// 	}
// 	return (str);
// }