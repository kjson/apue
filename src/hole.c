#include <stdio.h>
#include "apue.h"
#include <fcntl.h>


char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";


int main(void) {
    int     fd;

    // Try to open the file
    if ((fd = creat("var/file.hole", FILE_MODE)) < 0)
        err_sys("Creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("Write buf1 error");

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("Lseek error");

    if (write(fd, buf2, 10) != 10)
        err_sys("Write buf2 error");

    exit(0);
}
