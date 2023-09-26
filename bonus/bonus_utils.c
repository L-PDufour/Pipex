/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour </var/spool/mail/ldufour>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:17:17 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/22 09:17:17 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_pipes(t_pipex *pipex, int process_nb, int **pipes)
{
	pipex->j = -1;
	while (++pipex->j < process_nb)
	{
		close(pipes[pipex->j][0]);
		close(pipes[pipex->j][1]);
	}
}

void	file_creation_bonus(char **argv, t_pipex *pipex, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	exit_pipex(pipex->infile, "Error with infile", pipex);
	exit_pipex(pipex->outfile, "Error with outfile", pipex);
}

int	**pipes_creation(int pipes_nb, t_pipex *pipex)
{
	int	**pipes;

	pipex->i = -1;
	pipex->j = -1;
	pipes = (int **)malloc(pipes_nb * sizeof(int *));
	if (!pipes)
		return (NULL);
	while (++pipex->i < pipes_nb)
	{
		pipes[pipex->i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[pipex->i])
			return (NULL);
		pipex->j = -1;
		while (++pipex->j < 2)
			pipes[pipex->i][pipex->j] = pipex->j;
	}
	pipex->i = -1;
	while (++pipex->i < pipes_nb)
		pipe(pipes[pipex->i]);
	return (pipes);
	free(pipes);
}

void	free_pipes(int **pipes, t_pipex *pipex, int pipes_nb)
{
	pipex->i = -1;
	pipex->j = -1;
	while (++pipex->i < pipes_nb)
		free(pipes[pipex->i]);
	free(pipes);
}
