
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n; 
    int sum = 0;
    int diag1 = 0;
    int diag2 = 0;
    scanf("%d",&n);
    int a[n][n];
    int a_j, a_i;
    for(a_i = 0; a_i < n; a_i++){
       for(a_j = 0; a_j < n; a_j++){
          
          scanf("%d",&a[a_i][a_j]);
          
          // top-left to bottom-right
          if (a_i == a_j)
              diag1 += a[a_i][a_j];     
          // top-right to bottom-left
          if (a_j == ((n - 1) - a_i))
              diag2 += a[a_i][a_j];
       }
    }
    
    sum = abs(diag1 - diag2);
    printf("%d",sum);
    return 0;
}


