#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void daemonize() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork falied\n");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        printf("Fork is succesful\n");
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        perror("Falied to create session\n");
        exit(EXIT_SUCCESS);
    }

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

}


int main() {
    daemonize();
    return 0;
}
