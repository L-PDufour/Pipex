# Pipex
* * *

## Ressources
 This [playlist](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

* * *
- Learn about Pipelines in Unix and process.
- We can use these external functs : open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
- At first, I was reading and watching videos. I was trying to have a mental model of the data I/O and the redirection.
- Next, I did some small example to help my understanding. I did a lot of rework and used a struct to help me.
  ```
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
}	
  ```
- 
