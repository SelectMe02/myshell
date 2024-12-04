#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "ls_command.h"

#define MAX_LINE 80
#define MAX_ARGS 10
#define BUF_SIZE 1024

void my_cat(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if(fd<0){
        perror("Open error");
    }
    char buffer[BUF_SIZE];
    ssize_t bytes_read;

    while((bytes_read = read(fd, buffer, BUF_SIZE))>0){
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(fd);
}


int main()
{
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while(1){
        //prompt
        printf("myshell> ");

        //read command...
        fgets(input, MAX_LINE, stdin);
        //printf("%s\n", input);

        //tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while(token != NULL){
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if(argv[0]==NULL){ // empty command
            continue;
        }

        if (strcmp(argv[0], "exit")==0){
            printf("Goodbye~\n");
            exit(0);
        } else if (strcmp(argv[0], "cd") == 0){
            chdir(argv[1]);
        }else if (strcmp(argv[0], "pwd")==0){
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        }else if(strcmp(argv[0], "ls")==0){
            my_ls();
        }else if(strcmp(argv[0], "cat")==0){
            // you code comes here....
            if (argv[1]==NULL){
                printf("cat: missing file operand\n");
            } else{
                my_cat(argv[1]);
                printf("\n");
            }
        }else{
            if(access(argv[0], X_OK)==0){
                pid_t pid = fork();
                if(pid == 0){
                    char *env[] = {NULL};
                    execve(argv[0], argv, env);
                    printf("execute %s\n", argv[0]);
                    exit(1);
                } else if (pid>0){
                    int status;
                    waitpid(pid, &status, 0);
                    printf("Finish : %d\n", WEXITSTATUS(status));
                } else{
                    perror("Fork Error");
                }
            }else{
                printf("command not found: %s\n", argv[0]);
            }
        }
    }

    return 0;
}