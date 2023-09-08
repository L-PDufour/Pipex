#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    int file_pipes[2], data_pro, pid, folder[2];
    const char data[] = "Hello Leon"; 
    char buffer[20];
    pipe(file_pipes);
    pipe(folder);
    pid = fork();
    char *filename = "output.txt";
    char *ch;
    FILE *fp;
    int count = 0;
    if (pid == 0)
    {
        write(file_pipes[1], filename, strlen(filename) );
        printf("Child process wrote filename");
        read(folder[0], ch, 1024);
        // printf("Wrote %d bytes\n", data_pro);
    }
    else {
    
        read(file_pipes[0], buffer, 10);
        fp = fopen(buffer, "r");
        while(!feof(fp)){
            ch[count] = fgetc(fp);
            count++;
        }
        fclose(fp);
        write(folder[1], ch, strlen(ch));
    }
    return 0;
} 

