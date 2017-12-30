//
// Created by Terry Hanoman on 9/22/17.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

int main(int argc, char*argv[]){
    FILE *file;
    file =  fopen(argv[1],"r");
    char line[50];
    fgets(line,50,file);
    int rc = atoi(&line[0]);
    int matrix[rc][rc];
    int og[rc][rc];
    //matrix = (int)malloc(sizeof(int)*(2*rc));
    {
        int i = 0;
        int j = 0;
        int count;
        //while ((fgets(line, 20, file)) != NULL) {
        for(count = 0;i<rc; count++){
            fgets(line, 50, file);
            char *iter = strtok(line, "\t");
            j = 0;
            for (; iter != NULL; iter = strtok(NULL, "\t")) {
                int num = atoi(iter);
                matrix[i][j] = num;
                //printf("%d %d %d\n", i, j, matrix[i][j]);
                j++;
            }
            i++;
        }
    }
    memcpy(og,matrix, sizeof(og));
    fgets(line, 50, file);
    int exp = atoi(&line[0]);
    int q;
    for(q = 1; q<exp;q++){
        char print = 'n';
        if (q == exp-1){
            print = 'y';
        }
        int tempmat[rc][rc];
        int i;
        int ti = 0, tj = 0;
        for(i = 0;i<rc;i++){
            int j;
            int a = 0;
            int k;
            tj = 0;
            for(k = 0;k<rc;k++) {
                for (j = 0; j < rc; j++) {
                    a += matrix[i][j] * og[j][k];
                }
                tempmat[ti][tj] = a;
                if(print == 'y') {
                    printf("%d\t",a);
                }
                a = 0;
                tj++;
            }
            if(print == 'y') {
                printf("\n");
            }

            ti++;

        }
        memcpy(matrix,tempmat, sizeof(tempmat));
    }
    return 0;
}
