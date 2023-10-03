/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:29:51 by ldufour           #+#    #+#             */
/*   Updated: 2023/09/19 13:29:51 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
 * Initialize the t_pipex struct with default values.
 *
 * This function allocates memory for a t_pipex struct and initializes its
 * members with default values, making it ready for use in the pipex program.
 * If the struct has already been initialized, it returns the existing instance.
 *
 * @return A pointer to the initialized t_pipex struct or NULL on failure.
 */

t_pipex	*init_struct(void)
{
	static t_pipex	*pipex;

	pipex = NULL;
	if (!pipex)
	{
		pipex = malloc(sizeof(*pipex));
		if (!pipex)
		{
			fprintf(stderr, "Malloc failure\n");
			exit(EXIT_FAILURE);
		}
		ft_bzero(pipex, sizeof(*pipex));
	}
	return (pipex);
}

/**
 * Free allocated resources and deallocate the t_pipex struct.
 *
 * This function is responsible for releasing memory allocated for various
 * components within the 't_pipex' struct, including environment paths and
 * command arguments, and then deallocates the 't_pipex' struct itself.
 *
 * @param pipex  A pointer to the t_pipex struct containing allocated resources.
 */

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->env_path != NULL)
	{
		while (pipex->env_path[++i] != NULL)
			free(pipex->env_path[i]);
		free(pipex->env_path);
	}
	if (pipex->cmd_path != NULL)
		free(pipex->cmd_path);
	if (pipex->cmd_args != NULL)
	{
		i = -1;
		while (pipex->cmd_args[++i] != NULL)
			free(pipex->cmd_args[i]);
		free(pipex->cmd_args);
	}
	free(pipex);
}

/**
 * Exit the pipex program with an error message and clean up resources.
 *
 * This function prints an error message to the standard error (stderr) stream,
 * frees resources associated with the 't_pipex' struct, and exits the program.
 *
 * @param str    The error message to be displayed.
 * @param pipex  A pointer to the t_pipex struct containing allocated resources.
 */

void	exit_pipex(int error, char *str, t_pipex *pipex)
{
	if (error == -1)
	{
		fprintf(stderr, "%s\n", str);
		free_pipex(pipex);
		exit(0);
	}
}

/*
 * Verify and set the command path for execution.
 *
 * This function verifies the existence and executable permission of the command
 * in the directories specified by the 'env_path' array. If a valid executable
 * command is found, it sets the 'cmd_path' member in the 't_pipex' struct.
 * If no valid command is found, it exits the program with an error message.
 *
 * @param pipex  A pointer to the t_pipex struct containing configuration
 * details.
 *
 * @return 0 on success (command found and executable), 1 on failure.
 */

int	path_verification(t_pipex *pipex)
{
	int		i;
	char	*str;

	i = 0;
	while (pipex->env_path[i] != NULL)
	{
		str = ft_strjoin(pipex->env_path[i], pipex->cmd_args[0]);
		if (access(str, F_OK | X_OK) == 0)
		{
			pipex->cmd_path = ft_strdup(str);
			free(str);
			return (0);
		}
		free(str);
		i++;
	}
	exit_pipex(-1, "Command not found", pipex);
	return (1);
}

/**
 * Create a path array from the PATH environment variable.
 *
 * This function parses the PATH environment variable to create an array of
 * directory paths,
	which can be used for command execution in the pipex program.
 * It sets up the 'env_path' member in the 't_pipex' struct.
 *
 * @param envp   An array of strings representing the environment variables.

	* @param pipex  A pointer to the t_pipex struct where 'env_path' will be stored.
 */

void	envp_path_creation(char **envp, t_pipex *pipex)
{
	char	*str;
	int		i;
	char	*temp;

	str = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			str = ft_substr(*envp, 5, ft_strlen(*envp));
			pipex->env_path = ft_split(str, ':');
			free(str);
			i = -1;
			while (pipex->env_path[++i] != NULL)
			{
				temp = ft_strjoin(pipex->env_path[i], "/");
				if (temp)
				{
					free(pipex->env_path[i]);
					pipex->env_path[i] = temp;
				}
			}
		}
		envp++;
	}
}
