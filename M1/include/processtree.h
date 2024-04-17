#pragma once
#ifndef PROCESSTREE_H
#define PROCESSTREE_H

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <assert.h>
#include "utils.h"

typedef struct processNode_t {
    char *name;
    int pid;
    int ppid;
    struct processNode_t *parent;
    struct processNode_t **children;
    int numChildren;
    int capacity;
} processNode;

typedef struct processTree_t {
    processNode *head;
} processTree;

void init_process_node(processNode *ptr, const char *name, int pid, int ppid, processNode *parent);

void init_process_tree(processTree *ptr);

void destroy_process_node(processNode *node);

void destroy_process_tree(processTree *tree);


void make_tree(processNode *ptr, processNode *pcr, int sz);

int init_tree(processTree *init);

#endif
