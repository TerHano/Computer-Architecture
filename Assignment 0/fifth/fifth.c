//
// Created by Terry Hanoman on 9/22/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(int argc, char*argv[]){
    FILE *file;
    file =  fopen(argv[1],"r");
    char line[50];
    fgets(line,50,file);
    int rc = atoi(&line[0]);
    int magic[rc][rc];
    {
        int i = 0;
        int j = 0;
        while ((fgets(line, 50, file)) != NULL) {
            char *iter = strtok(line, "\t");
            j = 0;
            for (; iter != NULL; iter = strtok(NULL, "\t")) {
                int num = atoi(iter);
                magic[i][j] = num;
                j++;
            }
            i++;
        }
    }
    char wizard = 'y';
    int magnum = -1;
    int i;
    int sum = 0, sum2 = 0, sum3 = 0;
    for(i = 0;i<rc;i++){
        int j;
        for(j = 0;j<rc;j++){
            sum += magic[i][j];
            sum2 += magic[j][i];
        }

        if(magnum == -1){
            magnum = sum;
            sum = 0;
            sum2 = 0;
        }
        else
        {
            if(sum != magnum || sum != sum2){
                wizard = 'n';
                break;
            }
        }
        sum = 0;
        sum2=0;
        sum3 += magic[i][i];
    }
    if(sum3 != magnum){
        wizard = 'n';
    }
    sum = 0;
    int j = rc - 1;
    for(i = 0;i<rc && j >= 0;i++){
        sum+= magic[i][j];
        j--;
    }
    if(sum != magnum){
        wizard = 'n';
    }
    if(wizard == 'n'){
        printf("not-magic\n");
    }
    else{
        printf("magic\n");
    }
    return 0;
}
