#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LENGTH 10
 
int
main(void)
{
    /* Length of the password */
    unsigned short int length = PASSWORD_LENGTH;

    /* Seed number for rand() */
    srand((unsigned int) time(0) + getpid());

    /* ASCII characters 33 to 126 */
    while(length--) {
        putchar(rand() % 94 + 33);
        srand(rand());
    }

    printf("\n");

    return 0;
}
