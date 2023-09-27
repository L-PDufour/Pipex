/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:30:20 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/20 07:29:32 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_Pipex
{
	char	**env_path;
	char	*cmd_path;
	char	**cmd_args;
	int		infile;
	int		outfile;
	int		fd[2];
	int		pids1;
	int		pids2;
	int		i;
	int		j;
	int		pids_bonus[];
}			t_pipex;

char	*get_next_line(int fd); // Provide the correct function signature
void		file_creation_bonus(char **argv, t_pipex *pipex, int argc);
void		free_pipes(int **pipes, t_pipex *pipex, int pipes_nb);
void		close_pipes(t_pipex *pipex, int pipes_nb, int **pipes);
void		child_process_1(char **argv, char **envp, t_pipex *pipex);
t_pipex		*init_struct(void);
void		child_process_2(char **argv, char **envp, t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
t_pipex		*init_struct(void);
void		file_creation(char **argv, t_pipex *pipex);
void		envp_path_creation(char **envp, t_pipex *pipex);
void		exit_pipex(int number, char *str, t_pipex *pipex);
int			path_verification(t_pipex *pipex);
int			**pipes_creation(int pipes_nb, t_pipex *pipex);

#endif
