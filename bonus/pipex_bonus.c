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

static void	child_process_1_bonus(char **argv, char **envp, t_pipex *pipex,
		int pipes[])
{
	exit_pipex(dup2(pipex->infile, STDIN_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[1], STDOUT_FILENO), "dup2 error", pipex);
	close(pipes[0]);
	close(pipex->infile);
	pipex->cmd_args = ft_split(argv[2], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 1", pipex);
}

static void	child_process_2_bonus(char **argv, char **envp, t_pipex *pipex,
		int pipes[], int argc)
{
	exit_pipex(dup2(pipex->outfile, STDOUT_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[0], STDIN_FILENO), "du2 error", pipex);
	close(pipes[1]);
	close(pipex->outfile);
	pipex->cmd_args = ft_split(argv[argc - 1], ' ');
	path_verification(pipex);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit_pipex(-1, "Can't execute child process 2", pipex);
}

static void	child_process_x_bonus(char **argv, char **envp, t_pipex *pipex,
		int pipes[][2], int i)
{
	exit_pipex(dup2(pipes[i - 1][0], STDOUT_FILENO), "dup2 error", pipex);
	exit_pipex(dup2(pipes[i][1], STDIN_FILENO), "du2 error", pipex);
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
	int		pipes[argc - 1][2];
	int		pids[argc - 3];
	int		i;

	i = -1;
	pipex = NULL;
	pipex = init_struct_bonus();
	if (argc < 5)
		exit_pipex(-1, "Invalid arguments", pipex);
	file_creation_bonus(argv, pipex, argc);
	envp_path_creation(envp, pipex);
	while (++i < argc - 1)
		pipe(pipes[i]);
	i = -1;
	while (++i < argc - 3)
	{
		pids[i] = fork();
		if (pids[i] == 0 && i == 0)
			child_process_1_bonus(argv, envp, pipex, pipes[i]);
		else if (pids[i] == 0 && i == argc - 3)
			child_process_2_bonus(argv, envp, pipex, pipes[i], argc);
		else if (pids[i] == 0)
			child_process_x_bonus(argv, envp, pipex, pipes, i);
	}
	for (int i = 0; i < argc -1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	// Wait for all child processes to complete
	for (int i = 0; i < argc - 3; i++)
		wait(NULL);
	free_pipex(pipex);
	return (0);
}
