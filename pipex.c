#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCESS_NUM (argc - 3)

// 1ere etape Creer une string avec envp PATH et avec split use ft_strchr or ft_strncmp

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
	printf("je suis dans path\n");
	while (pipex.env_path[i] != NULL)
	{
		str = ft_strjoin(pipex.env_path[i], pipex.cmd_args[0]);
		if (access(str, F_OK | X_OK) == 0)
		{
			pipex.cmd_path = ft_strdup(str);
			printf("%s exist and is executable\n", pipex.cmd_path);
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
				printf("%s\n", pipex.env_path[i]);
				i++;
			}
		}
		envp++;
	}
}

// void	pipex(int fd1, int fd2)
// {
// 	int		fd[2];
// 	pid_t	child1;
// 	pid_t	child2;
// 	else	child2_task;
//
// 	pipe(fd);
// 	child1 = fork();
// 	if (child1 < 0)
// 		return (perror("Fork: "));
// 	else
// 		child1_task;
// 	child2 = fork() if (child2 < 0) return (perror("Fork: "));
// }

int	main(int argc, char *argv[], char **envp)
{
	int		infile;
	int		outfile;
	char	**path;
	int		pids[PROCESS_NUM];
	int		pipes[PROCESS_NUM + 1][2];
	int fd[2];
	int		i;
	int		j;
	int		status;

	// if (argc < 5)
		// return (-1);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
	{
		perror("Error with file");
		return (errno);
	}
	path = NULL;
	envp_path_creation(envp);
	// i = 0;
	// while (i < PROCESS_NUM + 1)
	// {
	// 	if (pipe(pipes[i]) == -1)
	// 	{
	// 		perror("Problem with pipes");
	// 		return (1);
	// 	}
	// 	printf("pipes[%d] created\n", i);
	// 	i++;
	// }
	i = 0;
	pipe(fd);
	while (i < PROCESS_NUM)
	{
		pids[i] = fork();
		printf("fork[%d]\n", i);
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{ 
			close(fd[0]);

			dup2(fd[1], STDIN_FILENO);
			pipex.cmd_args = ft_split(argv[i + 2], ' ');
			path_verification();
			close(infile);
			execve(pipex.cmd_path, pipex.cmd_args, envp);
			return (0); // don't forget to exit the child process
		}
		else {
			close(fd[1]);
			dup2(fd[0], STDOUT_FILENO);
			waitpid(pids[i], NULL, 0);
		}
		// printf("fork[%d]", i);
		i++;
	}
	close(pipes[0][1]);
	close(pipes[PROCESS_NUM + 1][0]);
	for (i = 0; i < PROCESS_NUM; i++)
	{
		waitpid(pids[i], &status, 0);
		// printf("Child process %d (PID: %d) exited with status %d\n", i,
		// WEXITSTATUS(status));
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
