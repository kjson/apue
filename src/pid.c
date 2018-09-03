// Get's the current process's PID.
#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("This process has PID %ld\n", (long) getpid());
}
