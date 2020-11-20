#include "kernel/types.h"
#include "user.h"



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: sleep seconds\n");
        exit(1);
    }
    int second = atoi(argv[1]);
    sleep(second);
    exit(0);
}