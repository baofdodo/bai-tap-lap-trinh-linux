// bt4: mo mot file bat ki, su dung co O_APPEND,sau do
// seek ve dau file roi ghi mot vai du lieu vao file do
// du lieu se xuat hien o vi tri nao cua file???

//answer: open file voi co O_APPEND thi khi write() thi
// se ghi vao vi tri cuoi file bat chap dung lseek()
// truoc khi ghi
// it's useful khi co nhieu process cung ghi vao mot file
// thi no se khong ghi de du lieu lan nhau.

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<time.h>

int main(){
    int fd = open("./test.txt", O_RDWR | O_APPEND);
    lseek(fd, 0, SEEK_SET);
    char mydata[] = "123";
    write(fd, mydata, strlen(mydata));
    return 0;
}
