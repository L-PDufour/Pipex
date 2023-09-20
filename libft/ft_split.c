/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:41:13 by ldufour           #+#    #+#             */
/*   Updated: 2023/03/06 08:32:09 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	width(char const *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

static char	**freearray(char **array, int width)
{
	int	i;

	i = -1;
	while (++i < width && array[i] != 0)
		free(array[i]);
	free(array);
	return (0);
}

static int	worddup(char *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i + j] != '\0' && s[i + j] != c)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	array = ft_calloc(sizeof(char *), width(s, c) + 1);
	if (!array)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	while (++i < width(s, c))
	{
		k = 0;
		array[i] = ft_calloc(sizeof(char), worddup((char *)s, c, j) + 1);
		if (!array[i])
			return (freearray(array, i));
		while (s[j] == c && s[j] != '\0')
			j++;
		while (s[j] != c && s[j] != '\0')
			array[i][k++] = s[j++];
	}
	return (array);
}

// int main(void) 
// {
// 	char **array;
//     char str[] = "this is a test";
//     char delimiter = ' ';
//     int i = 0;
// 	printf("%d\n", i);
//     array = ft_split(0, 0);
// 	printf("%s\n", array[0]);
// 	// printf("%s\n", array[1]);
// 	// printf("%s\n", array[2]);
// 	// printf("%s\n", array[3]);

// 	// while (i < 3)
// 	// {
// 	// 	printf("%s\n", array[i]);
// 	// 	i++;
// 	// }
//     return 0;
// }
