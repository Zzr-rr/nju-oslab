#include "../include/utils.h"

int get_parent_pid(int pid) {
    char path[40], line[100], *p;
    int ppid = 0;

    // construct the file path.
    sprintf(path, "/proc/%d/status", pid);

    // open the file.
    FILE *statusf = fopen(path, "r");
    if (!statusf) {
        perror("failed open");
        return EXIT_FAILURE;     // fail to get.
    }

    while (fgets(line, 100, statusf)) {
        if (strncmp(line, "PPid:", 5) == 0) {
            p = line + 5;
            while (*p == ' ') p++;
            ppid = atoi(p);
            break;
        }
    }
    fclose(statusf);
    return ppid;
}

void read_files(const char *filepath, char *content) {
    FILE *file = fopen(filepath, "r");
    char ch;
    int pointer = 0;
    if (file == NULL) {
        return;
    }
    while ((ch = fgetc(file)) != EOF) {
        content[pointer++] = ch;
    }
    content[pointer] = '\0';

    if (pointer > 0 && content[pointer - 1] == '\n') {
        content[pointer - 1] = '\0';
    }

    fclose(file);
}

bool is_numeric(const char *str) {
    if (*str == '\0') {
        return false;
    }
    while (*str) {
        if (!isdigit((unsigned char) *str)) {
            return false;
        }
        str++;
    }
    return true;
}
