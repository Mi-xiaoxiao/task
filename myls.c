// 11.26 基本实现完全ls的功能（第一个完整版）
#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   //getopt
#include <sys/stat.h> // stat 
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/ioctl.h> //屏幕终端




int show_all=0;
int show_long=0;
int show_inode=0;
int show_blocks=0;
int show_time=0;
int show_r=0;
int show_R=0;
char g_current_path[4096] = ".";





//实现动态内存分布，定义结构体
typedef struct filelist{
    char** names;
    unsigned int len;
    unsigned int cap;
}filelist;





int init(filelist* a);
int cmpname(const void* a,const void* b);
int cmptime(const void* a,const void* b);
char* turn_power(unsigned int a);
int add(filelist*a,unsigned int extra);
int push(filelist* a,const char* name);
char* getcolor(mode_t mode);
void do_ls(const char* path);
void print_grid(filelist *list, const char *path);









int main(int argc,char *argv[]) {
    int opt;
    while((opt=getopt(argc,argv,"alistrR"))!=-1) {
        if(opt=='a'){
            show_all=1;
        }
        if(opt=='l'){
            show_long=1;
        }
        if(opt=='i'){
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
        if(opt=='R'){
            show_R=1;
        }
    }
    do_ls(".");
    return 0;
}










//字典序
int cmpname(const void* a,const void* b){
    return strcmp(*(const char**)a,*(const char**)b);
}



//最近修改序
int cmptime(const void* a,const void* b){
    struct stat x, y;
    char path_a[5000], path_b[5000];
    
    // 把全局路径和文件名拼起来
    snprintf(path_a, sizeof(path_a), "%s/%s", g_current_path, *(const char**)a);
    snprintf(path_b, sizeof(path_b), "%s/%s", g_current_path, *(const char**)b);
    
    lstat(path_a, &x);
    lstat(path_b, &y);
    
    if(x.st_mtime == y.st_mtime){
        return strcmp(*(const char**)a, *(const char**)b);
    }
    // 降序：新的在前
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




//颜色函数
char* getcolor(mode_t mode) {
    if (S_ISDIR(mode)){return "\033[34m";} //目录：蓝色
    if (S_ISLNK(mode)){return "\033[36m";} //链接,快捷方式：青色
    if (mode & S_IXUSR){return "\033[32m";} //可执行：绿色
    return "\033[0m";                      //普通文件：默认色
}




void do_ls(const char* path){
    strcpy(g_current_path, path);
    DIR *dir;
    struct dirent *entry;

    dir=opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    filelist list;

    if(init(&list)!=0){
        perror("init");
        return;
    }

    while ((entry=readdir(dir))!=NULL) {
        if(show_all==0&&entry->d_name[0]=='.') {
            continue;
        }
        int s=push(&list,entry->d_name);

        if(s!=0){
            perror("push"); 
            return;
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
        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, list.names[i]);

        if(lstat(full_path, &file_all)!=0){
            perror(full_path);
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

    // 分支 1：如果带了 -l 等参数，走长格式单行输出
    if (show_long==1 || show_blocks==1 || show_inode==1) {
        for (unsigned int i = 0; i < list.len; i++) {
            struct stat file_all; 
            char full_path[4096];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, list.names[i]);

            if(lstat(full_path,&file_all)==0){

                if(show_inode==1){
                    printf("%*lu ", max_inode, (unsigned long)file_all.st_ino);
                }

                if(show_blocks==1){
                    printf("%*lu ",max_blocks,(unsigned long)(file_all.st_blocks)/2);
                }

                if(show_long==1){
                    struct passwd *pw = getpwuid(file_all.st_uid);
                    const char *owner_name = pw ? pw->pw_name : "unknown";
                    struct group *gr = getgrgid(file_all.st_gid);
                    const char *group_name = gr ? gr->gr_name : "unknown";

                    char readable_time[50];
                    struct tm* time_first = localtime(&file_all.st_mtime);
                    if(time_first!=NULL){
                         strftime(readable_time, sizeof(readable_time), "%Y年%m月%d日 %H:%M", time_first);
                    }else{
                        strcpy(readable_time, "未知时间");
                    }
                    
                    char* power = turn_power(file_all.st_mode);
                    printf("%s ", power);
                    printf("%*lu ", max_links, (unsigned long)file_all.st_nlink);
                    printf("%-*s ", max_owner, owner_name);
                    printf("%-*s ", max_group, group_name);
                    printf("%*ld ", max_size, (long)file_all.st_size);
                    printf("%s ", readable_time);
                }

                if(isatty(STDOUT_FILENO)){
                    printf("%s%s\033[0m\n", getcolor(file_all.st_mode), list.names[i]);
                }else{
                    printf("%s\n",list.names[i]);
                }

            }else{
                perror("lstat");
            }
        }
    } 

    // 分支 2：如果是普通模式，直接把整个 list 交给网格排版函数！
    else {
        print_grid(&list, path);
    }

    // 统一处理 -R 递归（放在最后，确保当前目录全部打印完再进子目录）
    if (show_R == 1) {
        for (unsigned int i = 0; i < list.len; i++) {
            struct stat dir_stat;
            char full_path[4096];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, list.names[i]);
            
            if (lstat(full_path, &dir_stat) == 0 && S_ISDIR(dir_stat.st_mode)) {
                if (strcmp(list.names[i], ".") != 0 && strcmp(list.names[i], "..") != 0) {
                    printf("\n%s:\n", full_path);
                    do_ls(full_path); 
                }
            }
        }
    }

    for (unsigned int i=0;i<list.len;i++) {
        free(list.names[i]);
    }

    free(list.names);
    closedir(dir);
}




// 多列网格排版函数
void print_grid(filelist *list, const char *path) {
    // 1. 获取终端宽度
    int term_width = 80;
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        term_width = w.ws_col;
    }

    // 2. 找出最长的文件名
    int max_name_len = 0;
    for (unsigned int i = 0; i < list->len; i++) {
        int len = strlen(list->names[i]);
        if (len > max_name_len) max_name_len = len;
    }

    // 3. 计算列宽、列数和行数
    int col_width = max_name_len + 2; 
    int cols = term_width / col_width; 
    if (cols < 1) cols = 1; 
    
    int rows = (list->len + cols - 1) / cols; 

    // 4.按照列竖着打印
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int idx = c * rows + r; 
            
            if (idx < list->len) {
                char full_path[4096];
                snprintf(full_path, sizeof(full_path), "%s/%s", path, list->names[idx]);
                struct stat dir_stat;

                // 打印带颜色的名字
                if (lstat(full_path, &dir_stat) == 0 && isatty(STDOUT_FILENO)) {
                    printf("%s%s\033[0m", getcolor(dir_stat.st_mode), list->names[idx]);
                } else {
                    printf("%s", list->names[idx]);
                }

                // 补齐空格（如果不是最后一列）
                if (c != cols - 1) {
                    int print_len = strlen(list->names[idx]);
                    for (int space = print_len; space < col_width; space++) {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n"); 
    }

}

