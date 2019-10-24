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
    printf("In child_main, Child pid: %d\n", getpid());
}

int main(int argc, const char *argv[]) {
    printf("Main pid: %d\n", getpid());

    pid_t pid = clone(child_main, stack+STACK_SIZE, CLONE_NEWPID | SIGCHLD, NULL);
    assert(pid>0);
    printf("Child pid: %d\n", pid);

    assert(waitpid(pid, NULL, 0)>0);
    printf("Child has terminated\n");
    return 0;
}
