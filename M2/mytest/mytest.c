#include <stdio.h>
#include <ucontext.h>

#define STACK_SIZE 8192

ucontext_t main_context, child_context;

void child_function() {
    printf("In child function\n");
    // 切换回主上下文
    swapcontext(&child_context, &main_context);
    printf("Child function resumed\n");
    // 再次切换回主上下文
    swapcontext(&child_context, &main_context);
}

int main() {
    char child_stack[STACK_SIZE];

    // 获取当前主上下文
    getcontext(&child_context);
    child_context.uc_stack.ss_sp = child_stack;
    child_context.uc_stack.ss_size = sizeof(child_stack);
    child_context.uc_link = &main_context;

    // 设置新上下文并将其与子函数关联
    makecontext(&child_context, child_function, 0);

    printf("Switching to child context\n");
    // 切换到子上下文
    swapcontext(&main_context, &child_context);
    printf("Back to main context\n");

    // 再次切换到子上下文
    swapcontext(&main_context, &child_context);
    printf("Back to main context again\n");

    return 0;
}
