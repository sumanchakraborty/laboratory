
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

#if 0
struct array {
  int size;
  int row_size;
  int col_size;
  int data[SIZE][SIZE];
};
typedef struct array array2D;

int display(array2D *a);
#endif

int print(int *a);

int main () {

  int a[SIZE][SIZE] = {{1,3,5},
                       {6,4,8},
                       {7,9,2}};
  int size = sizeof(a) / sizeof(int);
  printf("size of array - %d \n", size);

//print((int **)a);
  print((int *)a);
#if 0
  a.size = SIZE * SIZE;
  a.row_size = SIZE;
  a.col_size = SIZE;

  display(&a);
#endif

  return 0;
}

int print(int *a) {
  int i = 0;
  int j = 0;

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
    //printf("%d, ", a[i][j]);
      printf("%d ", *((a+i*SIZE) + j));
    }
    printf("\n");
  }

  return 0;
}

#if 0
int display(array2D *a) {
  int i = 0;
  int j = 0;

  for (i = 0; i < a->row_size; i++) {
    for (j = 0; j < a->col_size; j++) {
      printf("%d, ", a->data[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int display(array2D *a) {
  int i = 0;
  int j = 0;

  for (i = 0; i < a->row_size; i++) {
    for (j = 0; j < a->col_size; j++) {
      printf("%d, ", a->data[i][j]);
    }
    printf("\n");
  }

  return 0;
}
#endif
