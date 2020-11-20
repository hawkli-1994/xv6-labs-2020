#include "kernel/types.h"
#include "user.h"//
// Created by 李科燃 on 2020/11/20.
//

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    int exitStatus = 0;
    char readbuffer[4];
    char *ping = "ping";
    char *pong = "pong";
    int pid;
    if (fork() == 0) {
        pid = getpid();
        read(p[0], readbuffer, 4);
        if (strcmp(ping, readbuffer)) {
            printf("%d: received %s\n", pid, ping);
            write(p[1], &pong, 4);
        } else {
            exitStatus = 1;
        }
    } else {
        pid = getpid();
        write(p[1], &ping, 4);

        wait(0);
        read(p[0], readbuffer, 4);

        if (strcmp(pong, readbuffer)) {
            printf("%d: received %s\n", pid, pong);
        } else {
            exitStatus = 1;
        }
    }
    close(p[0]);
    close(p[1]);
    exit(exitStatus);

}