#include "../include/processtree.h"

void init_process_node(processNode *ptr, const char *name, int pid, int ppid, processNode *parent) {
    assert(ptr != NULL);
    ptr->name = strdup(name);
    ptr->pid = pid;
    ptr->ppid = ppid;
    ptr->parent = parent;
    ptr->numChildren = 0;
    ptr->capacity = 8;
    ptr->children = (processNode **) malloc(sizeof(processNode *) * ptr->capacity);
}

void init_process_tree(processTree *ptr) {
    assert(ptr != NULL);
    ptr->head = malloc(sizeof(processNode));
}

void make_tree(processNode *ptr, processNode *pcr, int sz) {
    if (ptr == NULL) return;
    for (int i = 0; i < sz; ++i) {
        if (pcr[i].ppid == ptr->pid) {
            processNode *pcs = malloc(sizeof(processNode));
            init_process_node(pcs, pcr[i].name, pcr[i].pid, pcr[i].ppid, ptr);
            ptr->children[ptr->numChildren++] = pcs;
        }
    }
    for (int i = 0; i < ptr->numChildren; ++i) {
        make_tree(ptr->children[i], pcr, sz);
    }
}

void destroy_process_node(processNode *node) {
    if (node == NULL) return;
    // free all the node cursively.
    free(node->name);
    for (int i = 0; i < node->numChildren; ++i) {
        destroy_process_node(node->children[i]);
    }
    free(node->children);
    free(node);
}

void destroy_process_tree(processTree *tree) {
    destroy_process_node(tree->head);
    tree->head = NULL;
}

void destroy_processes(processNode *ptr, int numProcess) {
    assert(ptr != NULL);
    for (int i = 0; i < numProcess; ++i) {
        free(ptr[i].name);
        free(ptr[i].children);
    }
}

/**
 * The method will build the process tree by the following steps:
 * <br>1. Scan the dir and store the basic information of the process in the array. </br>
 * <br>2. Use the array to build the tree. </br>
 **/
int init_tree(processTree *init) {
    const int MAX_PROCESSES = 100;
    processNode processes[MAX_PROCESSES];
    int numProcesses = 0;

    DIR *proc_dir;    // the pointer of the directory input stream.
    struct dirent *entry; // used for the struct of the category.
    proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Failed to open /proc directory");
        return EXIT_FAILURE;
    }
    while ((entry = readdir(proc_dir)) != NULL) {
        if (is_numeric(entry->d_name)) {
            char *endPtr;
            char destination[50] = "";
            char content[256] = "";

            int pid = (int) strtol(entry->d_name, &endPtr, 10);
            int ppid = get_parent_pid(pid);
            // concat the path of the process.
            strcat(destination, "/proc/");
            strcat(destination, entry->d_name);
            strcat(destination, "/comm");

            read_files(destination, content);
            init_process_node(&processes[numProcesses], content, pid, ppid, NULL);
            numProcesses++;
        }
    }
    closedir(proc_dir);
    assert(init != NULL);

    for (int i = 0; i < numProcesses; ++i) {
        if (processes[i].ppid == 0) {
            init_process_node(init->head, processes[i].name, processes[i].pid, processes[i].ppid, NULL);
        }
    }
    assert(init->head != NULL);
    assert(init->head->children != NULL);
    make_tree(init->head, processes, numProcesses);
    destroy_processes(processes, numProcesses);
    // get the tree.
    return EXIT_SUCCESS;
}
