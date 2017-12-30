//
// Created by Terry Hanoman on 9/20/17.
//
#include <stdio.h>

void ends(char* str){
    char* i = str;
    char e = ' ';
    for(i = str;*i;i++){
        e = *i;
    }
    printf("%c",e);
}
int main(int argc, char *argv[]){
    int i;
    for(i=1;i<argc;i++){
        ends(argv[i]);
    }
    printf("\n");
    return 0;
}
