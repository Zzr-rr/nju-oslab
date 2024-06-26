#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>    // EXIT_SUCCESS
#include "include/output.h"
#include "include/processtree.h"

int main(int argc, char *argv[]) {
    int help = 0, version = 0, name = 0;
    for (int i = 0; i < argc; i++) {
        assert(argv[i]);  // C standard
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) version = 1;
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) help = 1;
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--name") == 0) name = 1;
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

    processTree *pcs = malloc(sizeof(processTree));
    if (pcs == NULL) { // None
        fprintf(stderr, "Memory allocation failed. \n");
        return EXIT_FAILURE;
    }
    init_process_tree(pcs);
    init_tree(pcs);
    if(name == 1) print_tree_with_name(pcs->head, 0);
    else print_tree(pcs->head, 0);
    destroy_process_tree(pcs);
    free(pcs);
    return EXIT_SUCCESS;
}
