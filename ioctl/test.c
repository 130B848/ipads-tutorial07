#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include "ioctl-dev.h"

#define TUTORIAL_DEV_NAME "/dev/tutorial_dev"

int main(void) {
    int size = 4 << 20;
    int fd = open(TUTORIAL_DEV_NAME, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Failed to open %s\n", TUTORIAL_DEV_NAME);
        return -1;
    }
    
    ioctl(fd, TUTORIAL_TEST_PRINT, NULL);

    unsigned long *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) {
        perror("MAP_FAILED");
        return -1;
    }

    mem[0] = 0x1234;

    ioctl(fd, TUTORIAL_TEST_PRINT, NULL);

    munmap(mem, size);
    close(fd);
    printf("Bye\n");
    return 0;
}
