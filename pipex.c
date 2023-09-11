#include "libft/libft.h"
#include <stdio.h>

// 1ere etape Creer une string avec envp PATH et avec split use ft_strchr or ft_strncmp

struct		Pipex
{
	char	**path;
}			pipex;

int	main(int argc, char *argv[], char **envp)
{
	char	**path;
	char	*str;
	int		i;

	i = 0;
	path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			str = ft_substr(*envp, 5, (ft_strlen(*envp)));
			pipex.path = ft_split(str, ':');
			free(str);
			while (pipex.path[i] != NULL)
			{
				ft_strcat(pipex.path[i], "/");
				printf("%s\n", pipex.path[i]);
				i++;
			}
		}
		*envp++;
	}
	i = 0;
	while (pipex.path[i] != NULL)
	{
		free(pipex.path[i]);
		i++;
	}
	free(pipex.path);
	i = 0;
	return (0);
}
