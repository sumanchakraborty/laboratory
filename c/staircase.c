
#include <stdio.h>
#define SPACE " "
#define HASH "#"
#define NEWL "\n"

#define STEPS 6

int main () {
    int this_space, this_hash;
    int no_hash = 1;
    int no_space = STEPS - 1;
    while (no_hash < STEPS + 1) {
        for (this_space = 0; this_space < no_space; this_space++)
            printf("%s", SPACE);
        for (this_hash = 0; this_hash < no_hash; this_hash++)
            printf("%s", HASH);
        printf("%s", NEWL);
        no_hash++;
        no_space--;
    }
}

