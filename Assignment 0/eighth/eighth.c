//
// Created by Terry Hanoman on 9/23/17.

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    int height;
    struct node *left, *right;
};
struct node * root = NULL;

struct node *insert(struct node *ptr,int data, int height){
    struct node *temp =(struct node*) malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    if(ptr == NULL){
        temp->height = height;
        printf("inserted %d \n",temp->height);
        return temp;
    }
    if(ptr->data == data){
        printf("duplicate\n");
    }
    if(data > ptr->data)
    {
        ptr->right = insert(ptr->right,data,++height);
    }
    if(data < ptr->data){
        ptr->left = insert(ptr->left, data,++height);
    }

    return ptr;
}
void search(struct node* ptr,int data) {
 if(ptr ==  NULL){
        printf("absent\n");
    }
    else {
     if (ptr->data == data) {
         printf("present %d\n", ptr->height);
     } else {
         if (data > ptr->data) {
             search(ptr->right, data);
         }
         if (data < ptr->data) {
             search(ptr->left, data);
         }
     }
 }
}

int main(int argc, char*argv[]) {
    FILE *file;
    file = fopen(argv[1], "r");
    char num[30];
    while (fgets(num, sizeof(num), file) != NULL) {
        if (num[0] == 'i') {
            root = insert(root, atoi(&num[1]), 1);
        } else {
            if (num[0] == 's') {
                search(root, atoi(&num[1]));
            } else {
                printf("error");
            }
        }
    }
    return 0;
}
