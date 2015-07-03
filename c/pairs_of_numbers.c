
/*
 * 
 * Find all pairs of numbers in a sorted array that added up to a given sum.
 * 
 * Take input sorted array = a, low = 0, high = a.length - 1, sum
 * WHILE : low < high
 * IF: a[low] + a[high] == sum
 * THEN : Print = a[low] , a[high]; low++; high--
 * ELSEIF : a[low] + a[high] < sum
 * THEN low++
 * ELSE high--
 * END
 *
 */

#include <stdio.h>
#define SUM 8

int main ()
{
  int array[] = {0,1,2,3,4,5,6,7,8,9};
  int low = 0;
  int high = (sizeof(array)/sizeof(int)) - 1;
  int sum = SUM;

  while (low < high) {
    if ((array[low] + array[high]) == sum) {
      printf("%d + %d = %d\n", array[low], array[high], sum);
      low++; high--;
    }
    else if ((array[low] + array[high]) < sum) {
      low++;
    }
    else {
      high--;
    }
  }

  return 0;
}
