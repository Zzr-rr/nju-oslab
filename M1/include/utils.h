#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // bool, true, false
#include <ctype.h> // isdigit

int get_parent_pid(int pid);

void read_files(const char *filepath, char *content);

bool is_numeric(const char *str);

#endif
