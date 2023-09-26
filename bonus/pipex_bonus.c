/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour </var/spool/mail/ldufour>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:30:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/25 20:54:09 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_process_1_bonus(char **argv, t_pipex *pipex, int **pipes,
		int process_nb)
{
	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[0][1], STDOUT_FILENO), "dup2 error", pipex);
	close_pipes(pipex, process_nb, pipes);
	close(pipex->infile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 1", pipex);
}

static void	child_process_2_bonus(char **argv, t_pipex *pipex, int **pipes,
		int pipes_nb)
{
	exit_pipex(dup2(pipex->outfile, STDOUT_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[pipes_nb - 1][0], STDIN_FILENO), "dup2 error", pipex);
	close_pipes(pipex, pipes_nb, pipes);
	close(pipex->outfile);
	pipex->cmd_args = ft_split(argv[pipes_nb + 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

static void	child_process_x_bonus(char **argv, t_pipex *pipex, int **pipes,
		int pipes_nb)
{
	exit_pipex(dup2(pipes[pipex->i - 1][0], STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[pipex->i][1], STDOUT_FILENO), "du2p error", pipex);
	close_pipes(pipex, pipes_nb, pipes);
	pipex->cmd_args = ft_split(argv[pipex->i + 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

void	pipex_process(t_pipex *pipex, int process_nb, char **argv, int pipes_nb,
		int **pipes)
{
	pipex->i = -1;
	while (++pipex->i < process_nb)
	{
		pipex->pids_bonus[pipex->i] = fork();
		if (pipex->pids_bonus[pipex->i] == 0 && pipex->i == 0)
			child_process_1_bonus(argv, pipex, pipes, pipes_nb);
		else if (pipex->pids_bonus[pipex->i] == 0 && pipex->i == process_nb - 1)
			child_process_2_bonus(argv, pipex, pipes, pipes_nb);
		else if (pipex->pids_bonus[pipex->i] == 0)
			child_process_x_bonus(argv, pipex, pipes, pipes_nb);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;
	int		process_nb;
	int		pipes_nb;
	int		**pipes;
	int		i;
	int		j;

	i = -1;
	process_nb = argc - 3;
	pipes_nb = argc - 4;
	pipex = NULL;
	pipex = init_struct();
	pipex->pids_nb = process_nb;
	if (argc < 5)
		exit_pipex(-1, "Invalid arguments", pipex);
	file_creation_bonus(argv, pipex, argc);
	envp_path_creation(envp, pipex);
	pipes = (int **)malloc(pipes_nb * sizeof(int *));
	while (++i < pipes_nb)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		j = -1;
		while (++j < 2)
			pipes[i][j] = j;
	}
	while (++pipex->i < pipes_nb)
		pipe(pipes[pipex->i]);
	pipex_process(pipex, process_nb, argv, pipes_nb, pipes);
	close_pipes(pipex, pipes_nb, pipes);
	pipex->i = -1;
	while (++pipex->i < process_nb)
		wait(NULL);
	free_pipex(pipex);
	return (0);
}
