
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define STRING "sample string"

/* debug - function, line number */
#define DEBUG(...)                            \
{                                             \
  FILE *fp = fopen ("/debug.dbg", "a");       \
  fprintf (fp, "\n %s : %d ",  __FUNCTION__,__LINE__); \
  fprintf (fp, __VA_ARGS__);                  \
  fprintf (fp, " - %llu", eclock_us());       \
  fclose (fp);                                \
}

/* text formating - underline */
#define UNDERLINE(string, byte) \
{                                                \
  int index = 0;                                 \
  int length = strlen(string);                   \
                                                 \
  for (index = 0; index < length; index++)       \
    printf(byte);                                \
                                                 \
  printf("\n");                                  \
}

/* start timer */
#define TIME_START \
    struct timeval start, end;\
    long seconds, useconds;\
    gettimeofday(&start, NULL);

/* elapsed time */
#define TIME_STOP \
    gettimeofday(&end, NULL);\
    seconds  = end.tv_sec  - start.tv_sec;\
    useconds = end.tv_usec - start.tv_usec;\
    printf("Elapsed time: %ld microsecond\n", useconds);

int main()
{
  int stringLen = 0;

  TIME_START;

  stringLen = strlen(STRING);
  DEBUG();

  printf("%s\n", STRING);
  DEBUG();

  UNDERLINE(STRING, "*");

  TIME_STOP;

  return 0;
}

