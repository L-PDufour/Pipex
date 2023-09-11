#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// 1ere etape Creer une string avec envp PATH et avec split use ft_strchr or ft_strncmp

struct		Pipex
{
	char	**path;
	char	*cmd1_path;
	char	**cmd1_args;
}			pipex;

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	path_verification(char **argv)
{
	int		i;
	char	*str;

	i = 0;
	while (pipex.path[i] != NULL)
	{
		str = ft_strjoin(pipex.path[i], pipex.cmd1_args[0]);
		if (access(str, F_OK | X_OK) == 0)
		{
			pipex.cmd1_path = ft_strdup(str);
			printf("%s exist and is executable", pipex.cmd1_path);
			free(str);
			return (0);
		}
		free(str);
		i++;
	}
	return (1);
}

void	envp_path_creation(char **envp)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
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
				// printf("%s\n", pipex.path[i]);
				i++;
			}
		}
		envp++;
	}
}
int	main(int argc, char *argv[], char **envp)
{
	int		infile;
	int		outfile;
	char	**path;
	int		i;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (-1);
	i = -1;
	path = NULL;
	envp_path_creation(envp);
	pipex.cmd1_args = ft_split(argv[2], ' ');
	if (path_verification(argv) != 0)
		perror("access");
	pipex.cmd1_args = ft_split(argv[2], ' ');
	execve(pipex.cmd1_path,  pipex.cmd1_args, envp);
	perror("exec");
	// printf("%s\n", argv[2]);
	// while (pipex.cmd1_args[++i] != NULL)
		// printf("%s\n", pipex.cmd1_args[i]);
	free_double_array(pipex.path);
	free(pipex.cmd1_path);
	return (0);
}
