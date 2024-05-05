#include <stdlib.h>
#include <assert.h>
#include <ucontext.h>
#include <stdbool.h>
#include <stdio.h>


struct co* co_start(const char *name, void (*func)(void *), void *arg);
void co_yield();
void co_wait(struct co *co);
void co_run(struct co *co);
