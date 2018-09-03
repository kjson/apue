// Copy using standard IO
#include <stdio.h>

int main(void) {
    int     c;
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            printf("Output Error");
            return 1;
        }
    }

    if (ferror(stdin))
        printf("Input Error");

    return 0;

}
