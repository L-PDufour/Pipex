/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour </var/spool/mail/ldufour>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:24:38 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/18 14:21:45 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

struct		s_Pipex
{
	char	**env_path;
	char	*cmd_path;
	char	**cmd_args;
	int		infile;
	int		outfile;
	int		fd[2];
	int		pids1;
	int		pids2;
};
void	freePipex(void);
void	error_handling(int function, char *str);
void	envp_path_creation(char **envp);
int	path_verification(void);
void	exit_pipex(char *str);

#endif
