# Pipex

- Learn about Pipelines in Unix and process.
- fork() create a child process id 0 who must end with wait() before the parent every time.
```
#include errno.h
while (wait(NULL) != -1 || errno != ECHILD);
return 0;
```
- wait the for multiple child to stop in case of multiple fork
