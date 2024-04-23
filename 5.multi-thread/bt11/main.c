#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

typedef struct{
    char *name;
    char *birth;
    char *phone;   
}human_t;

void *myfunc(void *arg){
    human_t *student = (human_t *)arg;
    if (student == NULL)
        printf("i'm thread 1, bye\n");
    else {
        printf("i'm thread 2\n");
        printf("%s\n", student->name);
        printf("%s\n", student->birth);
        printf("%s\n", student->phone);
    }    
}

int main(){
    human_t A = {"buihoangan", "1984", "0902654941"};
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, myfunc, NULL); // thread 1 pass NULL
    pthread_create(&thread2, NULL, myfunc, &A);   // thread 2 pass a student info
    
    sleep(1);
    pthread_join(thread1, NULL);
    return 0;
}