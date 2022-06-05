// 2x forken: 1x auf der obersten ebene und dann im "parent" branch des 1. forks nochmal
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pipe(fd);

    int pid = fork();
    if(pid == 0) { // Child 1
        char buf[5];
        wait(0);
        read(fd[0], buf, 5);
        printf("%s\n", buf);
        exit(0);
    } else { // pid != 0 -> Parentprozess
        // fork again
        int pid = fork();
        if(pid == 0) { // Child 2
            close(fd[0]);
            write(fd[1], "hi", 5);
            exit(0);
        } else { // Parent
            wait(0);
        }
    }
}