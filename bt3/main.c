//BT3: Tao file text va ghi du lieu bat ki
// Ghi ra man hinh cacs thong tin loai file, ten, last edit, size su dung struct stat

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<time.h>

struct myFileInfo {
    // loai file
    // name
    // last edit
    //size
};
int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <filename> \"text\"\n", argv[0]);
        printf("\tExample: %s hello.txt \"Hello world\"\n",argv[0]);
        return 0;
    }
    int fd = open(argv[1],O_RDWR | O_CREAT |O_APPEND, 00666 ); // 
    if (fd == -1)
    {
        perror("open");
        return -1;
    }
    
    //printf("%s %ld\n", argv[2], strlen(argv[2]));
    if(write(fd, argv[2], strlen(argv[2])) == -1){
        perror("write:");
        close(fd);
        return -1;
    }
    //doc file
    //boi vi sau khi write, file offset dang o cuoi file,
    //nen goi ham read() luc nay se tra ve 0
    // tai dinh vi file offset bang lenh lseek()
    lseek(fd, 0, SEEK_SET);
    
    char buff[20];
    int read_result = read(fd, buff, 21);
    //printf("%d\n", read_result);
    if(read_result== -1){
        perror("read:");
        return -1;
    };
    printf("File content (first 20 bytes): %s\n", buff);
    // lay thong tin file

    
    struct stat fileinfo_t;
    fstat(fd, &fileinfo_t);
    // nap cac thong tin can hien thi
    // file type: dung truong st_mode voi mask S_IFMT
    printf("File type: ");
    switch (fileinfo_t.st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("Regular file\n");
        break;
    case S_IFDIR:
        printf("Directory\n");
        break;
    case S_IFCHR:
        printf("Character device\n");
        break;
    case S_IFBLK:
        printf("Block device\n");
        break;
    case S_IFIFO:
        printf("FIFO or pipe\n");
        break;
    case S_IFSOCK:
        printf("Socket\n");
        break;
    case S_IFLNK:
        printf("Symbolick link\n");
        break;
    
    
    default:
        printf("Invalid file\n");
        break;
    }
    // file size
    printf("Kich thuoc: %ld bytes\n",fileinfo_t.st_size);
    // thoi gian thay doi file lan cuoi
    //struct timespec lastMod_tm = fileinfo_t.st_mtime;
    printf("Last modification time: %s\n", ctime(&fileinfo_t.st_mtime));
    return 0;
}