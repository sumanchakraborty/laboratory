
#define debug(msg, ...) {                                                             \
        FILE* log = fopen("/etc/suman", "a");                                         \
        fprintf(log, "DEBUG %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__);    \
        fclose(log);                                                                  \
}

