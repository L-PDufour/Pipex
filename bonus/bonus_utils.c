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

void	close_pipes(t_pipex *pipex, int pipes_nb)
{
	pipex->j = -1;
	while (++pipex->j < pipes_nb)
	{
		close(pipex->pipes[pipex->j][0]);
		close(pipex->pipes[pipex->j][1]);
	}
}

void	file_creation_bonus(char **argv, t_pipex *pipex, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	exit_pipex(pipex->infile, "Error with infile", pipex);
	exit_pipex(pipex->outfile, "Error with outfile", pipex);
}
