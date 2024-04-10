#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    pid_t child_pid = -1;
    printf("Hello, we are on process with pid: %d\n", getpid());
    child_pid = fork();
    // From here, we have two processes
    if(child_pid == 0){
        printf("****************\n");
        printf("We are in child process with pid: %d\n", getpid());
        printf("My parent process has pid: %d\n", getppid());
        printf("****************\n");
        while(1);
    }
    else{
        printf("****************\n");
        printf("We are in parent process with pid: %d\n", getpid());
        // wait for a process end
        
        
    }
    //printf("where am I, my pid %d\n", getpid());

    return 0;
}