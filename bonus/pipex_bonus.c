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
#include <stdlib.h>

static void	child_process_1_bonus(char **argv, char **envp, t_pipex *pipex,
		int pipes[][2])
{
	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup21 error", pipex);
	exit_pipex(dup2(pipes[0][1], STDOUT_FILENO), "dup21 error", pipex);
	close(pipes[0][0]);
	close(pipes[1][1]);
	close(pipes[1][0]);
	close(pipex->infile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 1", pipex);
}

static void	child_process_2_bonus(char **argv, char **envp, t_pipex *pipex,
		int pipes[][2], int argc)
{
	exit_pipex(dup2(pipex->outfile, STDOUT_FILENO), "dup22 error", pipex);
	exit_pipex(dup2(pipes[1][0], STDIN_FILENO), "dup22 error", pipex);
	close(pipes[1][1]);
	close(pipex->outfile);
	close(pipes[0][1]);
	close(pipes[0][0]);
	pipex->cmd_args = ft_split(argv[argc - 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

static void	child_process_x_bonus(char **argv, char **envp, t_pipex *pipex,
		int pipes[][2], int i)
{
	exit_pipex(dup2(pipes[0][0], STDIN_FILENO), "dup2x error", pipex);
	exit_pipex(dup2(pipes[1][1], STDOUT_FILENO), "du2px error", pipex);
	close(pipes[1][0]);
	close(pipes[0][1]);
	pipex->cmd_args = ft_split(argv[i + 2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

static void	file_creation_bonus(char **argv, t_pipex *pipex, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	exit_pipex(pipex->infile, "Error with infile", pipex);
	exit_pipex(pipex->outfile, "Error with outfile", pipex);
}

static t_pipex	*init_struct_bonus(void)
{
	static t_pipex	*pipex;

	if (!pipex)
	{
		pipex = malloc(sizeof(*pipex));
		if (!pipex)
			exit_pipex(-1, "Malloc failure", pipex);
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
	t_pipex	*pipex;
	int		process_nb;
	int		pipes_nb;
	int		i;
	int		pids[argc - 3];
	int		pipes[argc - 4][2];
	int		j;

	process_nb = argc - 3;
	pipes_nb = argc - 4;
	i = -1;
	pipex = NULL;
	pipex = init_struct_bonus();
	if (argc < 5)
		exit_pipex(-1, "Invalid arguments", pipex);
	file_creation_bonus(argv, pipex, argc);
	envp_path_creation(envp, pipex);
	while (++i < pipes_nb){
		pipe(pipes[i]);
		// printf("pipes creation %d\n", i);
	}
	i = -1;
	while (++i < process_nb)
	{
		// printf("pipes fork %d\n", i);
		pids[i] = fork();
		if (pids[i] == 0 && i == 0)
			child_process_1_bonus(argv, envp, pipex, pipes);
		else if (pids[i] == 0 && i == 2)
			child_process_2_bonus(argv, envp, pipex, pipes, argc);
		else if (pids[i] == 0 && i == 1)
			child_process_x_bonus(argv, envp, pipex, pipes, i);
		// printf("process loop %d\n", i);
	}
	for (j = 0; j < process_nb; j++)
	{
		if (j != process_nb)
		{
			close(pipes[j][0]);
		}
		if (j != 0)
		{
			close(pipes[j][1]);
			// printf("close %d\n", j);
		}
	}
	close(pipes[0][1]);
	close(pipes[1][0]);
	for (int i = 0; i < process_nb; i++)
	{
		wait(NULL);
		// printf("process wait %d\n", i);
	}
	free_pipex(pipex);
	return (0);
}
