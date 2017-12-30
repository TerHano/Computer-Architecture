//
// Created by Terry Hanoman on 9/19/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void sort(int size, int array[]){
    int index, data, j;
    for (index = 1; index < size; index++)
    {
        data = array[index];
        j = index-1;

        while (j >= 0 && array[j] > data)
        {
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = data;
    }
}

int main(int argc, char*argv[]) {
    FILE *file;
    file = fopen(argv[1],"r");
    char num[256];
    fgets(num, sizeof(num),file);
    int size = atoi(num);
    int list[size];
    fgets(num, sizeof(num),file);
    int i = 0;

    char *nums = strtok(num,"\t");
    while (nums != NULL) {
        list[i] = atoi(nums);
        //printf("%d, ", atoi(nums));
        i++;
        nums = strtok (NULL, "\t");
    }
    sort(size,list);
    int trav;
    for(trav = 0;trav<size;trav++){
        printf("%d\t", list[trav]);
    }
    printf("\n");
    return 0;
}
