// Simple shell that fork execs a user command
#include "apue.h"
#include <sys/wait.h>

int main(void) {
    char        buf[MAXLINE];
    pid_t       pid;
    int         status;

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        printf("-> ");

        if (strlen(buf) <= 1)
            continue;

        // Remove the newline
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0) {
            err_sys("Forking error");
        } else if (pid ==0) {
            execlp(buf, buf, (char*)0);
            err_ret("Couldn't execute: %s", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpit error");

    }

    exit(0);
}
