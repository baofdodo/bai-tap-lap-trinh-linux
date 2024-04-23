#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>


void CtrlCHandler(int sig){
    printf("\nHello");
    _exit(0);
}
int main(){
    signal(SIGINT, CtrlCHandler);
    while(1);

    return 0;
}