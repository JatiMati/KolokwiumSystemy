#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "client.h"

char client_name[100];

void handle_sigterm(int sig) {
    printf("%s: Terminating...\n", client_name);
    exit(0);
}

void handle_sigusr2(int sig) {
    printf("%s: Acknowledged\n", client_name);
}

void handle_sigint(int sig) {
    printf("%s: Shutting down\n", client_name);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Client: Name not provided\n");
        return 1;
    }

    strncpy(client_name, argv[1], sizeof(client_name));
    printf("Imię: %s initialized\n", client_name);

    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR2, handle_sigusr2);
    signal(SIGINT, handle_sigint);

    char msg[100];
    while (fgets(msg, sizeof(msg), stdin)) {
        if (strstr(msg, "Who are you"))
            printf("I am %s\n", client_name);
        else if (strstr(msg, "PID"))
            printf("%s: PID is %d\n", client_name, getpid());
        else
            printf("%s: Unknown message\n", client_name);
    }
    return 0;
}
