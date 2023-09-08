# Pipex
* * *

## Ressources
 This [playlist](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

* * *
- Learn about Pipelines in Unix and process.
- fork() create a child process id 0 who must end with wait() before the parent every time.
- create process from the parent
- wait the for multiple child to stop in case of multiple fork 
- FIFO need two open end to work
- Simulating the pipe in C ("ping -c 5 google.com | grep rtt")
- - Pipe  have two end
- - Stdout(write) |(route)| Stdin(read)
- Need to learn how to execute program
- fork(): Create a child process who inherit almost everything from the parent(ex: value, variable)
- pipe(): Create a channel between two process to exchange data. A (write)===(read). Everything must close, if not, the program still wait for data transfer.
- dup2(): Copy and switch a file descriptor. Ex: we can use dup2() to redirect stdin to another file.
- I have been reading and watching videos the past days. I'm trying to have a mental model of the data I/O and the redirection.
