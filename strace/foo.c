#include <unistd.h>
#include <fcntl.h>

int main(void) {
    open("./bar", O_CREAT|O_RDONLY);
    sleep(1200);
    return 0;
}
