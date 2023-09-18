/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour </var/spool/mail/ldufour>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:34:46 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/18 13:34:46 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	freePipex(void)
{
	int	i;

	i = -1;
	if (pipex.env_path != NULL)
	{
		while (pipex.env_path[++i] != NULL)
			free(pipex.env_path[i]);
		free(pipex.env_path);
	}
	if (pipex.cmd_path != NULL)
		free(pipex.cmd_path);
	if (pipex.cmd_args != NULL)
	{
		i = -1;
		while (pipex.cmd_args[++i] != NULL)
			free(pipex.cmd_args[i]);
		free(pipex.cmd_args);
	}
}

void	exit_pipex(char *str)
{
	printf("%s\n", str);
	freePipex();
	exit(0);
}
void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	path_verification(void)
{
	int		i;
	char	*str;

	i = 0;
	while (pipex.env_path[i] != NULL)
	{
		str = ft_strjoin(pipex.env_path[i], pipex.cmd_args[0]);
		if (access(str, F_OK | X_OK) == 0)
		{
			pipex.cmd_path = ft_strdup(str);
			free(str);
			return (0);
		}
		free(str);
		i++;
	}
	exit_pipex("Can't access file");
	return (1);
}

void	error_handling(int function, char *str)
{
	if (function == -1)
		exit_pipex(str);
}

void	envp_path_creation(char **envp)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			str = ft_substr(*envp, 5, (ft_strlen(*envp)));
			pipex.env_path = ft_split(str, ':');
			free(str);
			while (pipex.env_path[i] != NULL)
			{
				ft_strcat(pipex.env_path[i], "/");
				i++;
			}
		}
		envp++;
	}
}

