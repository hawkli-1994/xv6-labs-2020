#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char *params[MAXARG] = {0};
    char buf[512];
    char *p;
    for (int i = 0; i<argc-1; i++) {
        params[i] = argv[i+1];
    }
    params[argc - 1] = buf;
    p = buf;
    while (read(0, p, 1)) {
        if (*p == '\n') {
            *p = '\0';
            if (fork() == 0) {
                exec(params[0], params);
                exit(0);
            } else {
                p = buf;
                wait(0);
            }
        } else {
            p++;
        }
    }
    exit(0);
}