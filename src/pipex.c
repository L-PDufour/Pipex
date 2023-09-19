/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <ldufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:25:29 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/19 13:57:22 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process_1(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->infile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
}

void	child_process_2(char **argv, char **envp, t_pipex *pipex)
{
	int	status;

	waitpid(pipex->pids1, &status, 0);
	dup2(pipex->outfile, STDOUT_FILENO);
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	close(pipex->outfile);
	pipex->cmd_args = ft_split(argv[3], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
}

void	file_creation(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->infile < 0 || pipex->outfile < 0)
		exit_pipex("Error with file", pipex);
}

t_pipex	*init_struct(void)
{
	static t_pipex	*pipex;

	if (!pipex)
	{
		pipex = malloc(sizeof(*pipex));	
		if (!pipex)
			return (NULL);
		pipex->env_path = NULL;
		pipex->cmd_path = NULL;
		pipex->cmd_args = NULL;
		pipex->infile = 0;
		pipex->outfile = 0;
		pipex->fd[0] = 0;
		pipex->fd[1] = 0;
		pipex->pids1 = 0;
		pipex->pids2 = 0;
	}
	return (pipex);
}

int	main(int argc, char *argv[], char **envp)
{
	int	status;
	t_pipex	*pipex;

	pipex = NULL;
	pipex = init_struct();
	if (argc < 5)
		exit_pipex("Invalid arguments", pipex);
	file_creation(argv, pipex);
	envp_path_creation(envp, pipex);
	pipe(pipex->fd);
	pipex->pids1 = fork();
	if (pipex->pids1 == 0)
		child_process_1(argv, envp, pipex);
	pipex->pids2 = fork();
	if (pipex->pids2 == 0)
		child_process_2(argv, envp, pipex);
	if (pipex->pids1 == -1 || pipex->pids2 == -1)
		exit(EXIT_FAILURE);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pids1, &status, 0);
	waitpid(pipex->pids2, &status, 0);
	free_pipex(pipex);
	return (0);
}
