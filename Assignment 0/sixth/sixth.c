//
// Created by Terry Hanoman on 9/20/17.
//

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
void add(char *st, char ch)
{
    int size = (int) strlen(st);
    st[size] = ch;
    st[size+1] = '\0';
}
char *compress(char build[],char str[]){
    //char build[50] = {""};
    char* i = str;
    char letter = ' ';
    int count = 0;
    for(i = str;*i;i++){
        if( *i >= '0' && *i <= '9' ) {
            printf("error\n");
            exit(1);
        }
        if(i == (char*)' '){
            continue;
        }
        if (letter == ' '){
            letter = *i;
            count++;
        }
        else{
            if(*i == letter){
                count++;
            }
            else{
                char a = (char) (count + '0');
                //printf("%c%c",letter,a);
                add(build, letter);
                add(build, a);
                letter = ' ';
                count = 0;
                i--;
            }
        }
    }
    if(letter != ' ') {
        char a = (char) (count + '0');
        //printf("%c%c", letter, a);
        add(build, letter);
        add(build, a);
    }
    if(strlen(build)>strlen(str)){
        return str;
    }
    else{
        str = build;
        return str;
    }

}

int main(int argc, char *argv[]){
    char build[50] = {""};
    char *result = compress(build,argv[1]);
    printf("%s\n", result);
    return  0;

}
