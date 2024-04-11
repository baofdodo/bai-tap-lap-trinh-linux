#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>

void reapZombieHandler(){
    wait(NULL);
    printf("Child reaped\n");
}

int main(){
    pid_t child_pid = -1;    
    child_pid = fork();
    switch (child_pid)
    {
    case -1:
        perror("fork");
        break;
    case 0:         // child
        printf("Child (PID%ld) started\n", (long)getpid());
        sleep(3);
        printf("Child (PID%ld) exitting\n", (long)getpid());
        _exit(0); // normal termination
        break;
    default:        // parent
        printf("Parent (PID %ld) started\n", (long)getpid());
        signal(SIGCHLD, reapZombieHandler);
        sleep(10);   // ensure child exit before parent
                    // dont know parent doesn't sleep remaining seconds.
        sleep(1);
        printf("Parent will exit\n");
        break;
    }  

    return 0;
}