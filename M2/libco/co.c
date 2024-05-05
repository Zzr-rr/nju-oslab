#include "co.h"
#define DEFAULT_STACK_SIZE 1024 * 128
#define DEFAULT_CO_ROUTINES_SIZE 1024

enum STATE{INIT, RUNNABLE, RUNNING, SUSPEND, FINISHED};

// INIT：协程初始化状态
// RUNNABLE: 在协程初始化完成之后，进入可执行的状态
// RUNNING: 协程处于正在执行的状态
// SUSPEND: 协程执行后被暂停的状态
// FINISHED: 协程执行完成之后的状态

struct co {
    const char* name; // 指定协程的名字
    void (*func)(void *);
    void *arg;
    enum STATE state;
    char stack[DEFAULT_STACK_SIZE];
    ucontext_t context; // 协程上下文
};

struct schedule {
    int running_id;
    int size;
    int max_size;
    struct co **coroutines;
};

// 全局定义调度器
static struct schedule *schedule = NULL;
static bool if_schedule_inited = false;

void schedule_init(){
    schedule = (struct schedule *)malloc(sizeof(struct schedule));
    assert(schedule != NULL);
    schedule->running_id = -1;
    schedule->size = 0;
    schedule->max_size = DEFAULT_CO_ROUTINES_SIZE;
    schedule->coroutines = (struct co **)malloc(sizeof(struct co *) * schedule->max_size);
    assert(schedule->coroutines != NULL);
}


struct co *co_start(const char *name, void (*func)(void *), void *arg) {

    if(!if_schedule_inited) schedule_init();
    assert(schedule != NULL);
    // printf("co started, thread name is %s \n", name);
    struct co *cur_co = (struct co*)malloc(sizeof(struct co));
    assert(cur_co != NULL);

    // 初始化协程
    cur_co->state = INIT;
    cur_co->name = name;
    cur_co->func = func;
    cur_co->arg = arg;

    // 初始化当前上下文
    getcontext(&cur_co->context);
    cur_co->context.uc_stack.ss_sp = cur_co->stack;
    cur_co->context.uc_stack.ss_size = sizeof(cur_co->stack);
    cur_co->context.uc_link = NULL;

    cur_co->state = RUNNABLE;

    // 协程调度器用于调度协程
    schedule->coroutines[schedule->size++] = cur_co;

    return cur_co;
}

// 表示当前协程需要等待，直到co协程的执行完成才能继续执行
void co_wait(struct co *co) {
    while(co->state != FINISHED){
        co_yield();
    }
}

// 实现协程的切换，协程运行之后一直在CPU上运行。
// 直到func函数返回或调用co_yield使得当前运行的协程暂时放弃执行。
// 随机选择下一个系统中可运行的协程。
void co_yield() {
    int current = schedule->running_id;
    if(current != -1) schedule->coroutines[current]->state = SUSPEND;
    for(int i = 1; i < schedule->size + 1; ++i){
        int next = (current + i) % schedule->size;
        if(schedule->coroutines[next]->state == RUNNABLE || schedule->coroutines[next]->state == SUSPEND){
            schedule->running_id = next;
            schedule->coroutines[next]->state = RUNNING;
            if(current != -1){
                swapcontext(&schedule->coroutines[current]->context, &schedule->coroutines[next]->context);
            }
            else{
                setcontext(&schedule->coroutines[next]->context);
            }
            break;
        }
    }
}

void co_run(struct co *co) {
    assert(co != NULL);
    schedule->running_id = co - schedule->coroutines[0];
    co->state = RUNNING;
    co->func(co->arg);
    co->state = FINISHED;
    schedule->running_id = -1;
}