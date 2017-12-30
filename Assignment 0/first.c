//
// Created by Terry Hanoman on 9/19/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int size = 0;
typedef struct node_{
    int data;
    struct node_* next;
}node;
node *search(int data);

node *root = NULL;

node *insert(int data){
    node *inside = search(data);
    if(inside == NULL){
        node *temp = (node*)malloc(sizeof(node*));
        temp->data = data;
        temp->next = NULL;
        if(root == NULL){
            root = temp;
            size++;
        }
        else{
            node *ptr;
            node *prev = NULL;
            for(ptr = root;ptr != NULL;ptr = ptr->next){
                if(ptr->data > data){
                    if(prev == NULL){
                        temp->next = ptr;
                        root = temp;
                        ++size;
                        return root;
                    }
                    else{
                        temp->next = ptr;
                        prev->next = temp;
                        ++size;
                        return root;
                    }
                }
                else {
                    prev = ptr;
                }
            }
            prev->next = temp;
            ++size;
        }
    }
    return root;
}
node *delete(int data){
    node *ptr;
    node *prev = NULL;
    for(ptr = root;ptr != NULL;ptr = ptr->next){
        if(ptr->data == data){
            if(ptr == root){
                root = root->next;
                --size;
            }
            else{
                --size;
                prev->next = ptr->next;
            }
        }
        prev = ptr;
    }
    return root;
}
node *search(int data){
    node *ptr;
    for(ptr = root;ptr != NULL;ptr = ptr->next){
        if(ptr->data == data){
            return ptr;
        }
    }
    return NULL;
}
void trav(){
    node *ptr;
    for(ptr = root;ptr != NULL;ptr = ptr->next){
        printf("%d\t",ptr->data);
    }
}

int main(int argc, char*argv[]){
    FILE *file;
    int fd = open(argv[1],O_RDONLY);
    char *buff = (char*)malloc(100);
    read(fd,buff,100);

    file = fopen(argv[1],"r");
        char num[30];
        while (fgets(num, sizeof(num), file) != NULL) {
            if (num[0] == 'i') {
                insert(atoi(&num[1]));
            } else {
                delete(atoi(&num[1]));
            }
        }
        if(root ==NULL)
        {
            printf("%d",0);
        }
        else {
            printf("%d\n",size);
            trav();
        }
        printf("\n");
	return 0;
}
