#include "kernel/param.h"
#include "kernel/types.h"
#include "user.h"
#include "kernel/sysinfo.h"

int main (int argc, char *argv[]) {
    if (argc != 1) {
        exit(1);
    }
    struct sysinfo info;
    sysinfo();
    printf("free space:%d, used process num:%d\n", info., info.nproc);
    exit(0);
}