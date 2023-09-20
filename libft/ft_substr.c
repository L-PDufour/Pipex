/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:34:19 by ldufour           #+#    #+#             */
/*   Updated: 2023/03/06 08:34:21 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dest = ft_calloc(sizeof(char), (len) + 1);
	if (!dest)
		return (0);
	ft_strlcpy(dest, s + start, len + 1);
	return (dest);
}

// #include <stdio.h>
// int main()
// {
// 	char *test;
// 	test = ft_substr("hola", -1, 0);
// 	printf("%s\n", test);
//     test = ft_substr("lorem ipsum dolor sit amet", 7, 10);
// 	printf("%s\n", test);
//     test = ft_substr("lorem ipsum dolor sit amet", 7, 0);
// 	printf("%s\n", test);
//     test = ft_substr("lorem ipsum dolor sit amet", 0, 0);
// 	printf("%s\n", test);
//     test = ft_substr("lorem ipsum dolor sit amet", 400, 20);
// 	printf("%s\n", test);
// }
