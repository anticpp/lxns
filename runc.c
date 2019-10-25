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

static int child_main(void *command) {
    printf("In child, pid %d\n", getpid());
    sethostname("runc", strlen("runc"));
    int rv = execv(command, NULL);
    if(rv<0) {
        printf("Child execv command '%s' error '%s'\n", (char *)command, strerror(errno));
        return 1;
    }
}

int main(int argc, const char *argv[]) {
    if(argc<2) {
        printf("Usage: %s [command]\n", argv[0]);
        return 1;
    }
    pid_t pid = clone(child_main
                    , stack+STACK_SIZE
                    , CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWUTS | SIGCHLD
                    , (void*)argv[1]);
    assert(pid>0);
    assert(waitpid(pid, NULL, 0)>0);
    printf("Child terminated\n");
    return 0;
}
