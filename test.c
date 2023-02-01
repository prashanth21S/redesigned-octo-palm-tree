#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 

int thread_func(int arg) {
    int sum = 0;
    for(unsigned long i = 0; i < (1UL<<33); i++) {
        sum = sum + i;
        if(sched_getcpu() == arg){
                printf("Running on core %d!\n", arg);
                break;
        }
    }
    return sum;
} 

int main(int argc, char *argv[]) {
    char *arg = argv[1];
    int core = atoi(arg);
    /*     
    cpu_set_t set;     
    CPU_ZERO(&set);
    CPU_SET(core, &set);
    sched_setaffinity(getpid(), sizeof(set), &set);
    */
    for(int i = 0; i < 30; i++) {
        int pid = fork();
        if(pid == 0){
            thread_func(core);
            break;
        }
    }
    return 0;
}
