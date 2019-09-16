#include <stdio.h>
#include <stdlib.h>
#include "nbgc.h"

int main(int argc, char *argv[])
{int r;
    set_conio_terminal_mode();

    while (1) {
        /* do some work */
    r = nb_getch(); /* consume the character */
printf("No input\r\n");
    if(r > 0) printf("get a char %c\n\r", r);
    if(r == 'q') exit(0);
    }
}


