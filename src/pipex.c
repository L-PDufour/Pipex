/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <ldufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:25:29 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/18 14:23:41 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"



void	child_process_1(char **argv)
{
	error_handling(dup2(pipex.infile, STDIN_FILENO), "Failed dup2");
	error_handling(dup2(pipex.fd[1], STDOUT_FILENO), "Failed dup2");
	error_handling(close(pipex.fd[0]), "Failed close");
	error_handling(close(pipex.infile), "Failed close");
	pipex.cmd_args = ft_split(argv[2], ' ');
	path_verification();
	if (execve(pipex.cmd_path, pipex.cmd_args, NULL) == -1)
		exit_pipex("Failed child procees 1");
}

void	child_process_2(char **argv)
{
	int	status;

	waitpid(-1, &status, 0);
	error_handling(dup2(pipex.outfile, STDOUT_FILENO), "Failed dup2");
	error_handling(dup2(pipex.fd[0], STDIN_FILENO), "Failed dup2");
	error_handling(close(pipex.fd[1]), "Failed close");
	error_handling(close(pipex.outfile), "Failed close");
	pipex.cmd_args = ft_split(argv[3], ' ');
	path_verification();
	if (execve(pipex.cmd_path, pipex.cmd_args, NULL) == -1)
		exit_pipex("Failed child procees 2");
}

void	file_creation(char **argv)
{
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		exit_pipex("Error with file");
}
void	init_struct(void)
{
	pipex.env_path = NULL;
	pipex.cmd_path = NULL;
	pipex.cmd_args = NULL;
	pipex.infile = 0;
	pipex.outfile = 0;
	pipex.fd[0] = 0;
	pipex.fd[1] = 0;
	pipex.pids1 = 0;
	pipex.pids2 = 0;
}

int	main(int argc, char *argv[], char **envp)
{

	if (argc < 5)
		exit_pipex("Invalid arguments");
	init_struct();
	file_creation(argv);
	envp_path_creation(envp);
	pipe(pipex.fd);
	pipex.pids1 = fork();
	pipex.pids2 = fork();
	if (pipex.pids1 == -1 || pipex.pids2 == -1)
	{
		ft_putstr_fd("Error", STDERR_FILENO);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pipex.pids1 == 0)
		child_process_1(argv);
	if (pipex.pids2 == 0)
		child_process_2(argv);
	if (pipex.pids1 == -1 || pipex.pids2 == -1)
	{
		exit_pipex("Fork error");
	}
	close(pipex.fd[1]);
	close(pipex.fd[0]);
	freePipex();
	return (0);
}
