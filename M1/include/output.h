//
// Created by zhuzr on 4/17/24.
//

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include "processtree.h"

void print_version();

void print_help();

void print_tree(processNode *ptr, int depth);

void print_tree_with_name(processNode *ptr, int depth);

#endif //OUTPUT_H
