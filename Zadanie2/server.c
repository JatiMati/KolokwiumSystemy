#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

void run_server() {
    int i;
    int pipefd[4][2][2]; // [client][read=0/write=1][0/1]
    const char *names[4] = {"Anna", "Paul", "Rick", "Nina"};

    for (i = 0; i < 4; ++i) {
        pipe(pipefd[i][0]); // server -> client
        pipe(pipefd[i][1]); // client -> server

        pid_t pid = fork();
        if (pid == 0) {
            dup2(pipefd[i][0][0], STDIN_FILENO);  // read from server
            dup2(pipefd[i][1][1], STDOUT_FILENO); // write to server
            close(pipefd[i][0][1]);
            close(pipefd[i][1][0]);
            execl("./client", "./client", names[i], NULL);
        }
        close(pipefd[i][0][0]);
        close(pipefd[i][1][1]);

        write(pipefd[i][0][1], "Hello clients! Who are you?\n", 29);
        char buffer[100];
        read(pipefd[i][1][0], buffer, sizeof(buffer));
        printf("Server received: %s", buffer);

        write(pipefd[i][0][1], "Hello clients! Your PID?\n", 26);
        read(pipefd[i][1][0], buffer, sizeof(buffer));
        printf("Server received: %s", buffer);
    }
}
