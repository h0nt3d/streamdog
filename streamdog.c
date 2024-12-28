#include <fcntl.h>
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
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        perror("Falied to create session\n");
        exit(EXIT_SUCCESS);
    }

    signal(SIGCHLD, SIG_IGN);   //ignore signals from terminal
    signal(SIGHUP, SIG_IGN);

    pid = fork();   //second fork

    if (pid < 0) {
        perror("Fork Failed\n");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (chdir("/") < 0) {
        perror("Falied to change directory\n");
    }


}


int main() {
    daemonize();
    return 0;
}
