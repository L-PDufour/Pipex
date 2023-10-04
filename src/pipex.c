/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <ldufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:25:29 by ldufour           #+#    #+#             */
/*   Updated: 2023/10/04 13:40:30 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**parsing_arguments(char *argv)
{
	char	**argument;
	int		i;

	i = -1;
	argument = NULL;
	while (argv[++i] != '\0')
	{
		if (argv[i] != 32 && ft_iswhitespace(argv[i]) == 1)
			argv[i] = ' ';
	}
	argument = ft_split(argv, ' ');
	return (argument);
}

/*
 * Execute the first child process in the pipex program.
 *
 * This function is responsible for setting up the first child process in the
 * pipex program. It configures file descriptors, command execution, and
 * handles potential errors during the process execution.
 *
 * @param argv   An array of strings containing command-line arguments.
 * @param envp   An array of strings representing the environment variables.
 * @param pipex  A pointer to the t_pipex struct containing configuration
 * details.
 */
// "grep	line" "		wc -l	"

void	child_process_1(char **argv, char **envp, t_pipex *pipex)
{
	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipex->fd[1], STDOUT_FILENO), "dup2 error", pipex);
	close(pipex->fd[0]);
	close(pipex->infile);
	pipex->cmd_args = parsing_arguments(argv[2]);
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 1", pipex);
}

/*
 * Execute the second child process in the pipex program.
 *
 * This function is responsible for setting up the second child process in the
 * pipex program. It configures file descriptors, command execution, and
 * handles potential errors during the process execution.
 *
 * @param argv   An array of strings containing command-line arguments.
 * @param envp   An array of strings representing the environment variables.
 * @param pipex  A pointer to the t_pipex struct containing configuration
 * details.
 */

void	child_process_2(char **argv, char **envp, t_pipex *pipex)
{
	int	status;

	waitpid(pipex->pids1, &status, 0);
	exit_pipex(dup2(pipex->outfile, STDOUT_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipex->fd[0], STDIN_FILENO), "du2 error", pipex);
	close(pipex->fd[1]);
	close(pipex->outfile);
	pipex->cmd_args = parsing_arguments(argv[3]);
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

/* Create and set file descriptors for input and output files. This function 
 * takes the input and output file paths from the `argv` array
 * and opens the files, setting up the corresponding file descriptors in the
 * `t_pipex` struct for later use in the pipex program.
 *
 * @param argv   An array of strings containing command-line arguments.
 * @param pipex  A pointer to the t_pipex struct where file descriptors are
 * stored.
 */

void	file_creation(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	exit_pipex(pipex->infile, "Error with infile", pipex);
	exit_pipex(pipex->outfile, "Error with outfile", pipex);
}

/**
 * Main function for the pipex program.
 *
 * This function orchestrates the execution of the pipex program, which involves
 * creating processes, setting up pipes, and executing commands.
 *
 * @param argc  The number of command-line arguments.
 * @param argv  An array of strings containing the command-line arguments.
 * @param envp  An array of strings representing the environment variables.
 *
 * @return 0 on successful execution, non-zero on error.
 */

int	main(int argc, char *argv[], char **envp)
{
	int		status;
	t_pipex	*pipex;

	pipex = NULL;
	pipex = init_struct();
	if (argc != 5)
		exit_pipex(-1, "Invalid arguments \n", pipex);
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
		exit_pipex(-1, "Fork error", pipex);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->pids1, &status, 0);
	waitpid(pipex->pids2, &status, 0);
	free_pipex(pipex);
	return (0);
}
