#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "ls_command.h"

void my_ls(void){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if(dir==NULL){
        perror("opendir");
        exit(0);
    }else{
        while((entry = readdir(dir))!= NULL){
            if(entry->d_type == DT_DIR){
                printf("%s/\n", entry->d_name);
            }
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

