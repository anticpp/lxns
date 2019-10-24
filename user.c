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
    printf("Root directory in child\n");
    system("ls /");
}

int main(int argc, const char *argv[]) {
    printf("Root directory in main:\n");
    system("ls /");
    printf("\n");

    pid_t pid = clone(child_main, stack+STACK_SIZE, CLONE_NEWNS | SIGCHLD, NULL);
    assert(pid>0);

    assert(waitpid(pid, NULL, 0)>0);
    printf("Child has terminated\n");
    return 0;
}
