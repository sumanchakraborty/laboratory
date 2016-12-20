
/*************** PRINT *****************/

#define DEBUG(msg, ...) {                                                             \
        FILE* log = fopen("/etc/suman", "a");                                         \
        fprintf(log, "DEBUG %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__);    \
        fclose(log);                                                                  \
}

/*************** TIMER *****************/

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff;
}

#define TIMER_START                  \
    struct timeval before , after;   \
    gettimeofday(&before , NULL);

#define TIMER_RESET                  \
    gettimeofday(&before , NULL);

#define TIMER_STOP                   \
    gettimeofday(&after , NULL);     \
    printf("Total time elapsed : %.0lf us\n" , time_diff(before, after));

