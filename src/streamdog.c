#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>

void daemonize();
void sendNotification(const char *message);
int isProgramRunning(const char *programName);
char line[256];

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

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);
}

void sendNotification(const char *message) {
    char command[256];
    snprintf(command, sizeof(command), "notify-send 'streamdog' '%s'", message);
    system(command);
}

int isProgramRunning(const char *programName) {
    DIR *dir;
    struct dirent *entry;
    char path[256];
    FILE *fp;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Failed to open /proc directory");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(entry -> d_type == DT_DIR) {
            snprintf(path, sizeof(path), "/proc/%s/comm", entry -> d_name);

            fp = fopen(path, "r");
            if (fp != NULL) {
                if (fgets(line, sizeof(line), fp)) {
                    line[strcspn(line, "\n")] = 0;

                    if (strcmp(line, programName) == 0) {
                        fclose(fp);
                        closedir(dir);
                        return 1;
                    }

                }
                fclose(fp);
            }
        }
    }
    closedir(dir);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Invalid number of arguments (Make sure a target is set)\n");
        exit(EXIT_FAILURE);
    }

    else if (argc > 2) {
        printf("Error, too many arguments (only set 1 traget)\n");
        exit(EXIT_FAILURE);
    }

    printf("Welcome to streamdog 1.0\n");

    const char *programName = argv[1];

    daemonize();

    while(1) {
        if (isProgramRunning(programName))
            sendNotification(strcat(line," is running."));
        else {
            sendNotification("Target is not running.");
            exit(EXIT_FAILURE);
            break;
        }

        sleep(3600);
    }

    return 0;
}
