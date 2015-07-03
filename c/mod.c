
#include <stdio.h>
#define VALUE 45673

int main () {
    int mod_n = VALUE % 32;
    int mod_b = VALUE & 31;

    if (mod_n == mod_b) {
        printf("worked...\n");
    }
    else {
        printf("not worked...\n");
    }
}

