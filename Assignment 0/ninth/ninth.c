// Created by Terry Hanoman on 9/23/17.
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    int height;
    struct node *left, *right;
};
struct node * root = NULL;

struct node *insert(struct node *root,int data, int height){
    struct node *temp =(struct node*) malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    if(root == NULL){
        temp->height = height;
        printf("inserted %d \n",temp->height);
        return temp;
    }
    if(root->data == data){
        printf("duplicate\n");
    }
    if(data > root->data)
    {
        root->right = insert(root->right,data,++height);
    }
    if(data < root->data){
        root->left = insert(root->left, data,++height);
    }
    return root;
}
void search(struct node* root,int data) {
    if(root ==  NULL){
        printf("absent\n");
    }
    else {
        if (root->data == data) {
            printf("present %d\n", root->height);
        } else {
            if (data > root->data) {
                search(root->right, data);
            }
            if (data < root->data) {
                search(root->left, data);
            }
        }
    }
}
struct node* deletion(struct node *root, int data)
{
    if (root == NULL) {
        printf("fail\n");
        return root;
    }

    if (data < root->data)
        root->left = deletion(root->left, data);

    else if (data > root->data)
        root->right = deletion(root->right, data);

    else
    {
        if(root->left == NULL && root->right == NULL){
            root = NULL;
            free(root);
            printf("success\n");
            return NULL;
        }
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            temp->height--;
            free(root);
            printf("success\n");
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            temp->height--;
            free(root);
            printf("success");
            return temp;
        }

        struct node *min;
        for(min = root->right;min->left!=NULL;min = min->left){
        }
        struct node* temp = min;

        root->data = temp->data;

        root->right = deletion(root->right, temp->data);
    }
    return root;
}

int main(int arc, char*argv[]){
    FILE *file;
    file = fopen(argv[1],"r");
    char num[30];
    while (fgets(num, sizeof(num), file) != NULL) {
        if (num[0] == 'i') {
            root = insert(root,atoi(&num[1]),1);
        } else {
            if(num[0]=='s') {
                search(root, atoi(&num[1]));
            }
            else {
                if (num[0] == 'd') {
                    root = deletion(root, atoi(&num[1]));
                }
                else{
                    printf("error");
                }
            }

        }
    }
return 0;
}
