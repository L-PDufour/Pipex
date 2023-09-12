/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <ldufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:25:29 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/12 15:25:29 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


struct		s_Pipex
{
	char	**env_path;
	char	*cmd_path;
	char	**cmd_args;
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

int	path_verification(void)
{
	int		i;
	char	*str;

	i = 0;
	while (pipex.env_path[i] != NULL)
	{
		str = ft_strjoin(pipex.env_path[i], pipex.cmd_args[0]);
		if (access(str, F_OK | X_OK) == 0)
		{
			pipex.cmd_path = ft_strdup(str);
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
			pipex.env_path = ft_split(str, ':');
			free(str);
			while (pipex.env_path[i] != NULL)
			{
				ft_strcat(pipex.env_path[i], "/");
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
	int		pids1;
	int		pids2;
	int		fd[2];
	int		i;
	int		j;
	int		status;

	if (argc < 5)
		exit (EXIT_FAILURE);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
	{
		perror("Error with file");
		exit(EXIT_FAILURE);
	}
	path = NULL;
	envp_path_creation(envp);
	pipe(fd);
	pids1 = fork();
	pids2 = fork();
	if (pids1 == -1 || pids2 == -1 )
	{
		ft_putstr_fd("Error", STDERR_FILENO);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pids1 == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(infile);
		pipex.cmd_args = ft_split(argv[2], ' ');
		path_verification();
		execve(pipex.cmd_path, pipex.cmd_args, envp);
		return (0); // don't forget to exit the child process
	}
	if (pids2 == 0)
	{
		waitpid(-1, &status, 0);
		dup2(outfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(outfile);
		pipex.cmd_args = ft_split(argv[3], ' ');
		path_verification();
		execve(pipex.cmd_path, pipex.cmd_args, envp);
	}
	free_double_array(pipex.env_path);
	free(pipex.cmd_path);
	return (0);
}
// TODO Commencer le pipe,
// dup2 et execve,Je pourrais faire un fork et child 1 s'occupe de cmd1 et child 2 s'occupe de cmd2
// execve(pipex.cmd1_path, pipex.cmd1_args, envp);
// perror("exec");
// printf("%s\n", argv[2]);
// while (pipex.cmd1_args[++i] != NULL)
// printf("%s\n", pipex.cmd1_args[i]);
// Je pourrais avoir seulment une section path,
// cmd qui est associé aux child processus.
