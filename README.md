# Pipex
* * *

## Ressources
 This [playlist](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

* * *
- Learn about Pipelines in Unix and process.
- fork() create a child process id 0 who must end with wait() before the parent every time.
```
#include errno.h
while (wait(NULL) != -1 || errno != ECHILD);
return 0;
```
- create process from the parent
- wait the for multiple child to stop in case of multiple fork 
- FIFO need two open end to work
- Simulating the pipe in C ("ping -c 5 google.com | grep rtt")
- - Pipe  have two end
- - Stdout(write) |(route)| Stdin(read)
- Need to learn how to execute program
