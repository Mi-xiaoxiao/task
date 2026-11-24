//11.24 欠缺-R的部分，窗口对齐,颜色
#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   //getopt
#include <sys/stat.h> // stat 
#include <pwd.h>
#include <time.h>
#include <grp.h>

int show_all=0;
int show_long=0;
int show_inode=0;
int show_blocks=0;
int show_time=0;
int show_r=0;

//字典序
int cmpname(const void* a,const void* b){
    return strcmp(*(const char**)a,*(const char**)b);
}

//最近修改序
int cmptime(const void* a,const void* b){
    struct stat x,y;
    stat(*(const char**)a,&x);
    stat(*(const char**)b,&y);
    if(x.st_mtime==y.st_mtime){
        return strcmp(*(const char**)a,*(const char**)b);
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

//实现动态内存分布，定义结构体
typedef struct filelist{
    char** names;
    unsigned int len;
    unsigned int cap;
}filelist;

//初始化
int init(filelist* a){
    a->len=0;
    a->cap=64;
    a->names=malloc(a->cap*sizeof(char*));
    if(a->names==NULL){
        return -1;
    }
    return 0;
}

//检查&扩容
int add(filelist*a,unsigned int extra){
    unsigned int need=a->len+extra;
    if(need<=a->cap){
        return 0;
    }
    unsigned int newcap=a->cap*2;
    if(newcap<need){
        newcap=need;
    }
    char** newnames=realloc(a->names,newcap*sizeof(char*));
    if(newnames==NULL){
        return -1;
    }
    a->names=newnames;
    a->cap=newcap;
    return 0;
}

//添加
int push(filelist* a,const char* name){
    if(add(a,1)!=0){
        return -1;
    }
    a->names[a->len] = strdup(name);
    if (a->names[a->len] == NULL) {
        return -1; // strdup 失败（内存耗尽）
    }
    a->len++;
    return 0;
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

    filelist list;

    if(init(&list)!=0){
        perror("init");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(show_all==0&&entry->d_name[0] == '.') {
            continue;
        }
        int s=push(&list,entry->d_name);

        if(s!=0){
            perror("push"); 
            return 1;
        }
    }
    if(show_time==1){
        qsort(list.names,list.len,sizeof(char*),cmptime);
    }else{
        qsort(list.names,list.len,sizeof(char*),cmpname);
    }

    if (show_r==1) {
    char* tmp;
        for (int i=0,j=list.len-1;i<j;i++,j--) {
            tmp=list.names[i];
            list.names[i]=list.names[j];
            list.names[j]=tmp;    
        }
    }

    int max_inode=0,max_blocks=0,max_links=0,max_owner=0,max_group=0,max_size=0;
    int sum_blocks=0;

    for (unsigned int i = 0; i < list.len; i++) {
        struct stat file_all;
        if (stat(list.names[i], &file_all) != 0) {
            perror(list.names[i]);
            continue;
        }

        int w; 
        // 1. 算 inode 宽度
        if (show_inode == 1) {
            w = snprintf(NULL, 0, "%lu", (unsigned long)file_all.st_ino);
            if (w > max_inode) max_inode = w;
        }

        // 2. 算 blocks 宽度
        if (show_blocks==1||show_long==1) {
            w = snprintf(NULL, 0, "%lu", (unsigned long)(file_all.st_blocks)/2);
            sum_blocks+=file_all.st_blocks/2;
            if (w > max_blocks) max_blocks = w;
        }

        // 3. 算长格式里各个字段的宽度
        if (show_long == 1) {
            // 硬链接数
            w = snprintf(NULL, 0, "%lu", (unsigned long)file_all.st_nlink);
            if (w > max_links) max_links = w;

            // 大小
            w = snprintf(NULL, 0, "%ld", (long)file_all.st_size);
            if (w > max_size) max_size = w;

            // 属主名
            struct passwd *pw = getpwuid(file_all.st_uid);
            const char *owner = pw ? pw->pw_name : "unknown";
            w=snprintf(NULL, 0, "%s",owner);
            if (w > max_owner) max_owner = w;

            // 属组名
            struct group *gr = getgrgid(file_all.st_gid);
            const char *group = gr ? gr->gr_name : "unknown";
            w =snprintf(NULL, 0, "%s", group);
            if (w > max_group) max_group = w;
        }
    }

    if (show_long == 1 || show_blocks == 1) {
            printf("总计%d\n", sum_blocks);
        }

    for (int i = 0; i<list.len;i++) {
        
        if (show_long==1||show_blocks==1||show_inode==1){

            struct stat file_all; 

            if(stat(list.names[i],&file_all)==0){

                if(show_inode==1){
                    printf("%*lu ", max_inode, (unsigned long)file_all.st_ino);
                }

                if(show_blocks==1){
                    printf("%*lu ",max_blocks,(unsigned long)(file_all.st_blocks)/2);
                }


                if(show_long==1){

                    // 查主名
                    struct passwd *pw = getpwuid(file_all.st_uid);
                    const char *owner_name;
                    if(pw!=NULL){
                        owner_name = pw->pw_name; 
                    }else{
                        owner_name = "unknown";
                    }

                    // 查组名
                    struct group *gr = getgrgid(file_all.st_gid);
                    const char *group_name;
                    if(gr!=NULL){
                        group_name = gr->gr_name;
                    }else{
                    group_name = "unknown";
                    }

                    char readable_time[50];
                    struct tm* time_first;
                    time_first=localtime(&file_all.st_mtime);
                    if(time_first!=NULL){
                         strftime(readable_time, sizeof(readable_time), "%Y年%m月%d日 %H:%M", time_first);
                    }else{
                        strcpy(readable_time, "未知时间");
                    }
                    char* power=turn_power(file_all.st_mode);
                    printf("%s ", power);
                    printf("%*lu ", max_links, (unsigned long)file_all.st_nlink);
                    printf("%-*s ", max_owner, owner_name);
                    printf("%-*s ", max_group, group_name);
                    printf("%*ld ", max_size, (long)file_all.st_size);
                    printf("%s ", readable_time);
                }
                printf("%s", list.names[i]);
                printf("\n");

            } else {
                perror("stat"); 
            }
        }else{
            printf("%s\n", list.names[i]);
        }
    }

    for (unsigned int i = 0; i < list.len; i++) {
        free(list.names[i]);
    }
    free(list.names);

    closedir(dir);
    return 0;
}
