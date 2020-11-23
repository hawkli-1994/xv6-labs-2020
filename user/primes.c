//
// Created by 李科燃 on 2020/11/20.
//

#include "kernel/types.h"
#include "user/user.h"


int process(int base);

int main (int argc, char *argv[]) {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int p[2];
    int i;
    pipe(p);
    if (fork() == 0) {
        close(p[1]);
        process(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        int len = sizeof(primes) / 4;
        for (i = 0; i < len; i++) {
            write(p[1], &primes[i], 4);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}

int process(int input) {
    int processPipe[2];
    int buf;
    int* bufPoint = &buf;
    int isEmpty = read(input, bufPoint, 4);
    if (isEmpty == 0) {
        return 0;
    }
    printf("prime %d\n", buf);
    pipe(processPipe);
    if (fork() == 0) {
        close(processPipe[1]);
        process(processPipe[0]);
        close(processPipe[0]);
    } else {
        close(processPipe[0]);
        while (isEmpty != 0) {
            isEmpty = read(input, bufPoint, 4);
            if (isEmpty == 0) {
                break;
            } else {
                write(processPipe[1], bufPoint, 4);
            }
        }
        close(processPipe[1]);
        wait(0);
    }
    close(processPipe[0]);
    close(processPipe[1]);
    return 0;
}