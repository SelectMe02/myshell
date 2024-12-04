#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80
#define MAX_ARGS 10



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
        }
    }

    return 0;
}