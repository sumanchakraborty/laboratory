
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int kadane_max(int* list);

int main () {
//int list[] = {2, 3, -1, 2, -4};
  int list[] = {2, 3, -1, 2, -4};

  kadane_min(list);
  kadane_max(list);
  display(list);

  return 0;
}

int display(int* list)
{
  int index = 0;

  for(index = 0; index < SIZE; index++) {
    printf("%d, ", list[index]);
  }
  printf("\n");
}

int kadane_max(int* list)
{
  int index = 0;
  int cur_max, cur_R, cur_L;
  int fin_max, fin_R, fin_L;

  cur_max = cur_R = cur_L = 0;
  fin_max = fin_R = fin_L = 0;

  for(index = 0; index < SIZE; index++) {
    cur_max += list[index];
    if (cur_max > fin_max) {
      fin_max = cur_max;
      cur_R = index;
      fin_R = cur_R;
      fin_L = cur_L;
    }
    if (cur_max < 0) {
      cur_max = 0;
      cur_R = index + 1;
      cur_L = index + 1;
    }
  }

  printf("max sum = %d, [%d, %d]\n", fin_max, fin_L, fin_R);
}

int kadane_min(int* list)
{
  int index = 0;
  int cur_min, cur_R, cur_L;
  int fin_min, fin_R, fin_L;

  cur_min = cur_R = cur_L = 0;
  fin_min = fin_R = fin_L = 0;

  for(index = 0; index < SIZE; index++) {
    cur_min += list[index];
    if (cur_min < fin_min) {
      fin_min = cur_min;
      cur_R = index;
      fin_R = cur_R;
      fin_L = cur_L;
    }
    if (cur_min > 0) {
      cur_min = 0;
      cur_R = index + 1;
      cur_L = index + 1;
    }
  }

  printf("min sum = %d, [%d, %d]\n", fin_min, fin_L, fin_R);
}
