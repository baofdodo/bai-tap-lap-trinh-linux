#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

#define EXIT_CODE 111

void printWaitStatus(const char *msg,int status){
 if (msg !=NULL)
 printf("%s", msg);
 if (WIFEXITED(status)) {
 printf("childexited,status=%d\n",WEXITSTATUS(status));
 }else if(WIFSIGNALED(status)) {
 printf("childkilled bysignal %d(%s)",
 WTERMSIG(status), strsignal(WTERMSIG(status)));
 if (WCOREDUMP(status))
 printf("(coredumped)");
 printf("\n");
 }else if(WIFSTOPPED(status)) {
 printf("childstoppedbysignal %d(%s)\n",
 WSTOPSIG(status), strsignal(WSTOPSIG(status)));
 }else if(WIFCONTINUED(status))
 printf("childcontinued\n");
 }

int main(){
    pid_t child_pid = -1;    
    child_pid = fork();
    switch (child_pid)
    {
    case -1:
        perror("fork");
        break;
    case 0:         // child B
        sleep(30);  // give a chance to abnormal terminate B with 'kill -9 child_pid' command
        _exit(EXIT_CODE); // normal termination
        break;
    default:        // parent A
        printf("Parent (PID %ld) waiting for chid (PID %ld) end\n", (long)getpid(), (long)child_pid);
        int child_exit_status;
        waitpid(child_pid, &child_exit_status, 0);
        char *msg = "wating ...\n";
        printWaitStatus(msg, child_exit_status);
        //printf("Child (PID %ld) end with status: %d\n", (long)child_pid, child_exit_status>>8);
        break;
    }  

    return 0;
}