#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define BUFSIZE 4096
#define TESTSIZE 4096 * 100000

ssize_t cp(const char *source, const char *target, int flags);
ssize_t rfile(const char *filename, size_t nbyte);


int main(void) {

    ssize_t     written, test_size;
    clock_t     start, diff;
    int         msec;

    remove("var/Test.in");
    remove("var/Test.out");

    test_size = rfile("var/Test.in", TESTSIZE);

    // Just write to OS page cache.
    start = clock();
    if ((written = cp("var/Test.in", "var/Test.out", O_WRONLY | O_CREAT)) < 0) {
        err_sys("CP error");
    }

    diff = clock() - start;

    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Normal took %d seconds %d milliseconds\n", msec/1000, msec%1000);


    // Wait for physical IO to finish.
    start = clock();
    if ((written = cp("var/Test.in", "var/Test.out", O_WRONLY | O_CREAT | O_SYNC)) < 0) {
        err_sys("CP error");
    }

    diff = clock() - start;

    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("SYNC took %d seconds %d milliseconds\n", msec/1000, msec%1000);


    // Only wait for data to be physically written to dist and not metadata.
    start = clock();
    if ((written = cp("var/Test.in", "var/Test.out", O_WRONLY | O_CREAT | O_DSYNC)) < 0) {
        err_sys("CP error");
    }

    diff = clock() - start;

    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("SYNC took %d seconds %d milliseconds\n", msec/1000, msec%1000);
}


ssize_t rfile(const char *filename, size_t nbyte) {

    int         fd, rfd;
    ssize_t     rbyte = 0, cbyte = 0, tbyte = 0;
    char        buf[BUFSIZE];

    // Try to open filename
    if ((fd = open(filename, O_WRONLY | O_CREAT, 0777)) < 0)
        err_sys("Could not create file %s", filename);

    // Try to open dev random
    if ((rfd = open("/dev/urandom", O_RDWR)) < 0)
        err_sys("Could not open /dev/urandom");

    while (tbyte < nbyte) {
        if ((rbyte = read(rfd, buf, BUFSIZE)) < 0)
            err_sys("Could not read from /dev/urandom");

        if ((cbyte = write(fd, buf, rbyte)) < 0)
            err_sys("Could not write to %s", filename);

        tbyte += cbyte;

    }

    return tbyte;
}


ssize_t cp(const char *source, const char *target, int flags) {

    int         fd1, fd2;
    ssize_t     nbyte = 0, tbyte = 0;
    char buf[BUFSIZE];

    // Try to open source file.
    if ((fd1 = open(source, O_RDONLY)) < 0) {
        err_sys("Could not open source file\n");
    }

    if ((fd2 = open(target, flags, 0777)) < 0) {
        err_sys("Could not open target file\n");
    }

    while ((nbyte = read(fd1, buf, BUFSIZE)) > 0) {
        tbyte += nbyte;
        if (write(fd2, buf, nbyte) < 0) {
            err_sys("Write error.\n");
        }
    }

    return tbyte;

}
