/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour </var/spool/mail/ldufour>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:30:40 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/20 10:30:40 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_process_1_bonus(char **argv, t_pipex *pipex,
		int pipes[][2], int process_nb)
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

static void	child_process_2_bonus(char **argv, t_pipex *pipex,
		int pipes[][2], int pipes_nb)
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

static void	child_process_x_bonus(char **argv, t_pipex *pipex,
		int pipes[][2], int pipes_nb)
{
	exit_pipex(dup2(pipes[pipex->i - 1][0], STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[pipex->i][1], STDOUT_FILENO), "du2p error", pipex);
	close_pipes(pipex, pipes_nb, pipes);
	pipex->cmd_args = ft_split(argv[pipex->i + 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

void	pipex_process(t_pipex *pipex, int process_nb, char **argv, int pipes_nb, int pipes[][2])
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

void	pids_creation_bonus( int argc, int number)
{
	int fd[argc * number];
	// // pipex->pids_bonus = (int *)malloc(sizeof(int) * pipex->pids_nb); 
	// *pipex->pids_bonus =  pipex->pids_nb; 

}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;
	int		process_nb;
	int		pipes_nb;
	int		pipes[argc - 4][2];

	process_nb = argc - 3;
	pipes_nb = argc - 4;
	// pipex->pids_bonus[] = process_nb
	pipex = NULL;
	pipex = init_struct();
	pipex->pids_nb = process_nb;
	// pids_creation_bonus(pipex, argc);
	if (argc < 5)
		exit_pipex(-1, "Invalid arguments", pipex);
	file_creation_bonus(argv, pipex, argc);
	envp_path_creation(envp, pipex);
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
