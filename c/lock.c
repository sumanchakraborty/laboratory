#include <fcntl.h>
#include <unistd.h>

int main () {
    int fd;
    int status;
    struct flock f1;

    f1.l_type = F_WRLCK;
    f1.l_whence = SEEK_SET;
    f1.l_start = 0;
    f1.l_len = 0;
    f1.l_pid = getpid();

    fd = open("/mnt/suman/foo", O_WRONLY);
    fcntl(fd, F_SETLKW, &f1);
    status = close(fd);
    return status;
}
