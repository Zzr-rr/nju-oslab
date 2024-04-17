//
// Created by zhuzr on 4/17/24.
//
#include "../include/output.h"

void print_version() {
    printf("rPstree UNKNOWN\n");
    printf("Copyright (C) 1993-2019 Werner Almesberger and CragiSmall\n\n");
    printf("rPstree version 0.0.1 (Ubuntu 9.4.0-Ubuntu 22.04.3)\n");
}

void print_help() {
    printf("Display a tree of processes.\n");
    printf(" -v, --version\t\tdisplay version information\n");
    printf(" -h, --help\t\tdisplay help information\n");
    printf(" -p, --show-pids\tshow PIDs; implies -c\n");
}

void print_tree(processNode *ptr) {
    if (ptr == NULL) return;
    printf("pid: %d ", ptr->pid);
    printf("ppid: %d ", ptr->ppid);
    printf("name: %s ", ptr->name);
    for (int i = 0; i < ptr->numChildren; ++i) {
        print_tree(ptr->children[i]);
    }
}