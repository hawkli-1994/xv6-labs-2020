//
// Created by 李科燃 on 2020/11/23.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *name);

char* fmtname(char *path) {
    char *p;
    for(p=path+strlen(path); p >= path && *p != '/'; p--);
    return ++p;
}

void find (char *path, char *name) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: %s: No such file or directory\n", path);
        return;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: %s: No such file or directory\n", path);
        close(fd);
        return;
    }
    switch (st.type) {
        case T_FILE:
            if (strcmp(fmtname(path), name) == 0) {
                printf("%s\n", path);
            }
            break;
        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                printf("ls: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
                if (strcmp(de.name, ".") == 0) {
                    continue;
                }
                if (strcmp(de.name, "..") == 0) {
                    continue;
                }
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf, name);
            }
            break;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if(argc <= 2){
        printf("usage: params is not enf\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}