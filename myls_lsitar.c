//11.23 实现-lastri命令任意组合使用，欠缺-R的部分，动态内存调整，窗口对齐
#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   //getopt
#include <sys/stat.h> // stat 结构体和函数都在这里
#include <time.h>

int show_all=0;
int show_long=0;
int show_inode=0;
int show_blocks=0;
int show_time=0;
int show_r=0;

//字典序
int cmpname(const void* a,const void* b){
    return strcmp((const char*)a,(const char*)b);
}

//最近修改序
int cmptime(const void* a,const void* b){
    struct stat x,y;
    stat((const char*)a,&x);
    stat((const char*)b,&y);
    if(x.st_mtime==y.st_mtime){
        return strcmp((const char*)a,(const char*)b);
    }
    return y.st_mtime-x.st_mtime;
}

//权限（6位八进制数）的转化
char* turn_power(unsigned int a){
    static char s[11];
    s[10]='\0';
    if(S_ISDIR(a)){
        s[0]='d';
    }else if(S_ISLNK(a)){
        s[0]='l';
    }else if(S_ISREG(a)){
        s[0]='-';
    }else{
        s[0]='?';
    }
    for(int i=0;i<3;i++){
        int sign=(a>>(6-i*3))&7;
        switch(sign){
            case 0:memcpy(&s[1+i*3],"---",3);break;
            case 1:memcpy(&s[1+i*3],"--x",3);break;
            case 2:memcpy(&s[1+i*3],"-w-",3);break;
            case 3:memcpy(&s[1+i*3],"-wx",3);break;
            case 4:memcpy(&s[1+i*3],"r--",3);break;
            case 5:memcpy(&s[1+i*3],"r-x",3);break;
            case 6:memcpy(&s[1+i*3],"rw-",3);break;
            case 7:memcpy(&s[1+i*3],"rwx",3);break;
        }
    }
    return s;
}

int main(int argc,char *argv[]) {

    DIR *dir;
    struct dirent *entry;

    int opt;
    while ((opt=getopt(argc, argv, "alistr"))!= -1) {
        if (opt=='a') {
            show_all=1;
        }
        if(opt=='l'){
            show_long=1;
        }
        if (opt=='i') {
            show_inode=1;
        }
        if(opt=='s'){
            show_blocks=1;
        }
        if(opt=='t'){
            show_time=1;
        }
        if(opt=='r'){
            show_r=1;
        }
    }
    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    int file_count=0;
    char file_name[1000][256];

    while ((entry = readdir(dir)) != NULL) {
        if(show_all==0&&entry->d_name[0] == '.') {
            continue;
        }
        strcpy(file_name[file_count],entry->d_name);
        file_count++;
        if(file_count>=1000){
            break;
        }
    }
    if(show_time==1){
        qsort(file_name,file_count,sizeof(file_name[0]),cmptime);
    }else{
        qsort(file_name,file_count,sizeof(file_name[0]),cmpname);
    }

    if (show_r==1) {
    char tmp[256];
    for (int i=0,j=file_count-1; i<j;i++,j--) {
        memcpy(tmp,file_name[i], 256);
        memcpy(file_name[i],file_name[j],256);
        memcpy(file_name[j],tmp,256);
    }
}

        for (int i = 0; i < file_count; i++) {
        
        if (show_long==1||show_blocks==1||show_inode==1){

            struct stat file_all; 

            if(stat(file_name[i],&file_all)==0){

                if(show_long==1){
                    char readable_time[50];
                    struct tm* time_first;
                    time_first=localtime(&file_all.st_mtime);
                    if (time_first!=NULL){
                         strftime(readable_time, sizeof(readable_time), "%Y年%m月%d日 %H:%M", time_first);
                    }else{
                        strcpy(readable_time, "未知时间");
                    }
                    char* power=turn_power(file_all.st_mode);
                    printf("%s\t %ld\t %s\t %s\t ",power,file_all.st_size,readable_time,file_name[i]);
                }

                if(show_blocks==1){
                    printf("%lu\t ",(file_all.st_blocks)/2);
                }

                if(show_inode==1){
                    printf("%lu\t ",file_all.st_ino);
                }
                
                printf("\n");
            } else {
                perror("stat"); 
            }
        } 
        else {
            printf("%s\n", file_name[i]);
        }
    }
    closedir(dir);
    return 0;
}
