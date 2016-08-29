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
4
1112
1912
1892
1234
*/

int cavity(char **grid, int n);
int is_cavity(char **grid, int r, int c);

int main(){
    int n = 0, grid_i = 0; 
    scanf("%d",&n);
    char* grid[n];
    for(grid_i = 0; grid_i < n; grid_i++){
        grid[grid_i] = (char *)malloc(1024 * sizeof(char));
        scanf("%s",grid[grid_i]);
    }
    cavity(grid, n);
    return 0;
}

int cavity(char **grid, int n)
{
    int ri = 0, ci = 0;
    for (ri = 0; ri < n; ri++) {
        for (ci = 0; ci < n; ci++) {
            // consider border 
            if (ri == 0 || ri == n-1 ||
                ci == 0 || ci == n-1) {
                printf("%c", grid[ri][ci]);
                continue;
            }
            if(is_cavity(grid, ri, ci))
                printf("X");
            else
                printf("%c", grid[ri][ci]);
        }
        printf("\n");
    }
    return 1;
}

int is_cavity(char **grid, int r, int c)
{
    if ((grid[r][c] > grid[r-1][c]) &&
        (grid[r][c] > grid[r+1][c]) &&
        (grid[r][c] > grid[r][c-1]) &&
        (grid[r][c] > grid[r][c+1])) {
        return 1;
    }
    return 0;
}

