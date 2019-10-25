#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#define STACK_SIZE (1024 * 1024)

static char stack[STACK_SIZE];

static int child_main() {
    printf("Network in child:\n");
    system("ip link");
}

int main(int argc, const char *argv[]) {
    printf("Network in main:\n");
    system("ip link");
    printf("\n");

    pid_t pid = clone(child_main, stack+STACK_SIZE, CLONE_NEWNET | SIGCHLD, NULL);
    assert(pid>0);

    assert(waitpid(pid, NULL, 0)>0);
    return 0;
}
