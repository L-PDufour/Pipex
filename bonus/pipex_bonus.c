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

static void	child_process_1_bonus(char **argv, t_pipex *pipex, int pipes_nb)
{
	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipex->pipes[0][1], STDOUT_FILENO), "dup2 error", pipex);
	close_pipes(pipex, pipes_nb);
	close(pipex->infile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 1", pipex);
}

static void	child_process_2_bonus(char **argv, t_pipex *pipex, int pipes_nb)
{
	exit_pipex(dup2(pipex->outfile, STDOUT_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipex->pipes[pipes_nb - 1][0], STDIN_FILENO), "dup2 error", pipex);
	close_pipes(pipex, pipes_nb);
	close(pipex->outfile);
	pipex->cmd_args = ft_split(argv[pipes_nb + 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

static void	child_process_x_bonus(char **argv, t_pipex *pipex, int pipes_nb)
{
	exit_pipex(dup2(pipex->pipes[pipex->i - 1][0], STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipex->pipes[pipex->i][1], STDOUT_FILENO), "du2p error", pipex);
	close_pipes(pipex, pipes_nb);
	pipex->cmd_args = ft_split(argv[pipex->i + 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, NULL);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

void	pipex_process(t_pipex *pipex, int process_nb, char **argv)	
{
	pipex->i = -1;
	while (++pipex->i < process_nb)
	{
		pipex->pids[pipex->i] = fork();
		if (pipex->pids[pipex->i] == 0 && pipex->i == 0)
			child_process_1_bonus(argv, pipex, process_nb + 1);
		else if (pipex->pids[pipex->i] == 0 && pipex->i == process_nb - 1)
			child_process_2_bonus(argv, pipex, process_nb + 1);
		else if (pipex->pids[pipex->i] == 0)
			child_process_x_bonus(argv, pipex, process_nb + 1);
	}
}

void	creates_pipes(t_pipex *pipex, int process_nb)
{
	int	rows;
	int	columns;
	int i;
	int j;

	i = -1;
	rows = process_nb + 1;
	columns = 2;
	pipex->pipes = (int **)malloc(rows * sizeof(int *));
	if (pipex->pipes == NULL)
	{
		perror("malloc");
		exit(1); // Error handling
	}
	while (++i < rows)
	{
		pipex->pipes[i] = (int *)malloc(columns * sizeof(int));
		printf("pipex->pipex[%d]\n", *pipex->pipes[i]);
		if (pipex->pipes[i] == NULL)
		{
			perror("malloc");
			exit(1); // Error handling
		}
		j = -1;
		while (++j < columns)
		{
			pipex->pipes[i][j] = j;
		}

	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;
	int		process_nb;

	process_nb = argc - 3;
	pipex = NULL;
	pipex = init_struct();
	pipex->pids = (int *)malloc(process_nb * sizeof(int));
	creates_pipes(pipex, process_nb + 1);
	if (pipex->pids == NULL)
		return (1);
	if (argc < 5)
		exit_pipex(-1, "Invalid arguments", pipex);
	file_creation_bonus(argv, pipex, argc);
	envp_path_creation(envp, pipex);
	while (++pipex->i < process_nb + 1)
		pipe(pipex->pipes[pipex->i]);
	pipex_process(pipex, process_nb, argv);
	close_pipes(pipex, process_nb + 1);
	pipex->i = -1;
	while (++pipex->i < process_nb)
		wait(NULL);
	free_pipex(pipex);
	return (0);
}
