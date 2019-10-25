#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>
#include <unistd.h>

static void print_nodename() {
    struct utsname utsname;
    uname(&utsname);
    printf("%s\n", utsname.nodename);

}

#define STACK_SIZE (1024 * 1024)

static char stack[STACK_SIZE];

static int child_main() {
    printf("Child UTS nodename: ");
    print_nodename();

    printf("Change child's UTS nodename\n");
    sethostname("yezhihui-node-demo", strlen("yezhihui-node-demo"));

    printf("New child UTS nodename: ");
    print_nodename();
}

int main(int argc, const char *argv[]) {
    printf("Main UTS nodename: ");
    print_nodename();

    pid_t pid = clone(child_main, stack+STACK_SIZE, CLONE_NEWUTS | SIGCHLD, NULL);
    assert(pid>0);
    sleep(2);

    printf("Main UTS nodename after clone: ");
    print_nodename();

    assert(waitpid(pid, NULL, 0)>0);
    return 0;
}
