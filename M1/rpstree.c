#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>    // EXIT_SUCCESS
#include "include/utils.h"
#include "include/output.h"
#include "include/processtree.h"

typedef struct {
    int PID;
    int parentPID;
    char name[40];
} Process;

void test() {
    DIR *proc_dir;    // the pointer of the directory input stream.
    struct dirent *entry; // used for the struct of the category.
    proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Failed to open /proc directory");
        return;
    }
    while ((entry = readdir(proc_dir)) != NULL) {
        if (is_numeric(entry->d_name)) {
            char *endPtr;
            char destination[50] = "";
            char content[1024] = "";
            int pid = (int) strtol(entry->d_name, &endPtr, 10);
            int ppid = get_parent_pid(pid);
            // concat the path of the process.
            strcat(destination, "/proc/");
            strcat(destination, entry->d_name);
            strcat(destination, "/comm");

            read_files(destination, content);

            printf("pid:%d ", pid);
            printf("ppid:%d ", ppid);
            printf("%s\n", content);
        }
    }
    closedir(proc_dir);
}

int main(int argc, char *argv[]) {
    int help = 0, version = 0;
    for (int i = 0; i < argc; i++) {
        assert(argv[i]);  // C standard
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) version = 1;
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) help = 1;
    }
    assert(!argv[argc]); // C standard
    if (version == 1) {
        print_version();
        return EXIT_SUCCESS;
    }
    if (help == 1) {
        print_help();
        return EXIT_SUCCESS;
    }
    // Process pcs[1024];
    test();
    return EXIT_SUCCESS;
}
