/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:30:30 by ldufour           #+#    #+#             */
/*   Updated: 2023/03/06 08:30:35 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;

	if (!s)
		return (NULL);
	ch = (unsigned char) c;
	str = (unsigned char *) s;
	while (n--)
	{
		if (*str != ch)
			str++;
		else
			return (str);
	}
	return (0);
}
