#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/*
INPUT_FORMAT
------------
1
10 10
7283455864
6731158619
8988242643
3830589324
2229505813
5633845374
6473530293
7053106601
0834282956
4607924137
3 4
9505
3845
3530

*/

int is_equal(char **G, char **P, int ro, int co, int r, int c);
int is_found(char **G, char **P, int R, int C, int r, int c);

int main() {
    int t, a0;
    scanf("%d",&t);
    for(a0 = 0; a0 < t; a0++) {
        int R; 
        int C; 
        int G_i;
        scanf("%d %d",&R,&C);
        char* G[R];
        for(G_i = 0; G_i < R; G_i++){
            G[G_i] = (char *)malloc(1024 * sizeof(char));
            scanf("%s",G[G_i]);
        }
        int r; 
        int c; 
        int P_i;
        scanf("%d %d",&r,&c);
        char* P[r];
        for(P_i = 0; P_i < r; P_i++){
            P[P_i] = (char *)malloc(1024 * sizeof(char));
            scanf("%s",P[P_i]);
        }

        printf ("Matrix Found? %s\n", is_found(G, P, R, C, r, c)?"yes":"no");
    }
    return 0;
}

int is_found(char **G, char **P, int R, int C, int r, int c)
{
    int ro = 0, co = 0; 
    for (ro = 0; ro + r <= R; ro++) {
        for (co = 0; co + c <= C; co++) {
            if (is_equal(G, P, ro, co, r, c))
                return 1;
        }
    }
    return 0;
}

int is_equal(char **G, char **P, int ro, int co, int r, int c)
{
    int ri = 0, ci = 0;
    for (ri = 0; ri < r; ri++) {
        for (ci = 0; ci < c; ci++) {
            if (G[ro+ri][co+ci] != P[ri][ci]) 
                return 0;
        }
    }
    return 1;
}
