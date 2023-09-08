#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/wait.h"
#include "unistd.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// example ./pipex file1 cmd1 cmd2 file2
// < file1 cmd1 | cmd2 > file2
// Convert execlp to execve
int	main(int argc, char **argv)
{
	int	pipe_fd[2];

	pid_t child1, child2;
	// Create a pipe
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// Fork the first child process (cmd1)
	child1 = fork();
	if (child1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child1 == 0)
	{
		// Child process (cmd1)
		close(pipe_fd[0]); // Close the read end of the pipe
		dup2(pipe_fd[1], STDOUT_FILENO);
		// Redirect stdout to the write end of the pipe
		close(pipe_fd[1]); // Close the write end of the pipe
		// Execute cmd1 (e.g., "cat file1" in this example)
		printf("ICI");
		char *const output[] = {"echo", "test ", ">" ," ouput.txt", NULL};
		execve("/bin/echo", output, NULL);
		perror("exec");
		exit(EXIT_FAILURE);
	}
	else
	{
		// Parent process
		// Fork the second child process (cmd2)
		child2 = fork();
		if (child2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child2 == 0)
		{
			// Child process (cmd2)
			close(pipe_fd[1]); // Close the write end of the pipe
			dup2(pipe_fd[0], STDIN_FILENO);
			// Redirect stdin to the read end of the pipe
			close(pipe_fd[0]); // Close the read end of the pipe
			// Execute cmd2 (e.g., "grep keyword" in this example)
			execlp("grep", "grep", "test", NULL);
			perror("exec");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			close(pipe_fd[0]); // Close both ends of the pipe
			close(pipe_fd[1]);
			// Wait for both child processes to complete
			waitpid(child1, NULL, 0);
			waitpid(child2, NULL, 0);
		}
	}
	return (0);
}
