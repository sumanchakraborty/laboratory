#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define NEW_LINE        '\n'
#define PASSWORD_COUNT  15
#define PASSWORD_LENGTH 10
#define PASSWORD_CHAR   '#'
#define PASSWORD_FILE   "psswd.txt"
 
int
main(void)
{
    FILE *fp = 0;
    time_t now = 0;
    /* number of passwords */
    short int count = 0;
    /* length of the password */
    unsigned short int length = 0;

    /* open file */
    fp = fopen(PASSWORD_FILE, "a");
    now = time(NULL);

    /* seed number for rand() */
  //srand((unsigned int) time(0) + getpid());
    srand((unsigned int) now + getpid());

    fprintf(fp, "%s", ctime(&now));

    /* number of passwords */
    for (count = 0; count < PASSWORD_COUNT; count++) {
        /* header */
        putc(PASSWORD_CHAR, fp);

        /* length of each password */
        length = PASSWORD_LENGTH - 2;

        /* ascii characters 33 to 126 */
        while(length--) {
            putc(rand() % 94 + 33, fp);
            srand(rand());
        }

        /* footer */
        putc(PASSWORD_CHAR, fp);
        putc(NEW_LINE, fp);
    }

    /* close file */
    fclose(fp);

    system ("cat "PASSWORD_FILE);

    return 0;
}

