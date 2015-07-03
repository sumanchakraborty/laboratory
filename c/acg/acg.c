
#include <stdio.h>
#include <string.h>

#define FILE_IN  "input.acg"
#define FILE_OUT "output.acg"

int main()
{

  FILE *iFile = 0;
  FILE *oFile = 0;

  iFile = fopen(FILE_OUT, "w");

  fprintf(iFile, "testing...\n");

  fclose(iFile);
}
