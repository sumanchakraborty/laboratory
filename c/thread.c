#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

double time_diff(struct timeval x , struct timeval y);
#define TIMER_START \
    struct timeval before , after;\
    gettimeofday(&before , NULL);

#define TIMER_RESET \
    gettimeofday(&before , NULL);

#define TIMER_STOP \
    gettimeofday(&after , NULL);\
    printf("Total time elapsed : %.0lf us\n" , time_diff(before, after));

#define NTHREADS 100

#define ARRAY_SIZE 100000000
long int array[ARRAY_SIZE];
long int array_sum;
long int array_segment_sum[NTHREADS];

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff;
}

long int array_init() {
    long int i = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    return 0;
}

long int array_reset() {
    long int i = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 0;
    }
    return 0;
}

long int array_add() {
    long int i = 2;
    long int sum = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    printf("the sum of array elements %llu\n", sum);
    return 0;
}

void *thread_func(void *x)
{
    long int i, base, tid, elements;
    tid = *((long int *) x);
    elements = ARRAY_SIZE/NTHREADS;
    base = tid * elements;
  //printf("thread[%d] base - %d\n", tid, base);
    for (i = 0; i < elements; i++)
        array_segment_sum[tid] += array[base + i];
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread[NTHREADS];
    long int thread_args[NTHREADS];
    long int rc, i;
    long int sum = 0;

#if 1
    array_reset();
    array_init();
    TIMER_START
    array_add();
    TIMER_STOP
#endif

    TIMER_RESET
#if 1
    /* spawn the threads */
    for (i=0; i<NTHREADS; ++i) {
        thread_args[i] = i;
      //printf("\nspawning thread %d\n", i);
        rc = pthread_create(&thread[i], NULL, thread_func, (void *) &thread_args[i]);
    }

    /* wait for threads to finish */
    for (i=0; i<NTHREADS; ++i) {
        rc = pthread_join(thread[i], NULL);
    }

    for (i=0; i<NTHREADS; ++i) {
        sum += array_segment_sum[i];
    }
    TIMER_STOP

    printf("\nsum %lu\n", sum);
#endif
    return 1;
}
