#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void daemonize() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork falied");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        printf("Fork is succesful\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    daemonize();
    return 0;
}
