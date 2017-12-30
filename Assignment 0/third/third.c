//
// Created by Terry Hanoman on 9/21/17.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int buckets = 10000;
struct hash {
    struct node *root;
    int count;
};

struct node {
    int data;
    struct node *next;
};
struct node *Hashnode(int data) {
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

struct hash *table = NULL;

void insertHash(int data) {
    int ptr = data % buckets;
    if(ptr < 0){
        ptr = ptr*-1;
    }
    struct node *temp = Hashnode(data);
    if (table[ptr].root == NULL) {
        table[ptr].root = temp;
        table[ptr].count = 1;
        printf("inserted\n");
        return;
    }
    struct node *check = (table[ptr].root);

    temp->next = (table[ptr].root);

    while (check != NULL) {
        if (check->data == data) {
            printf("duplicate\n");
            return;
        }
        check = check->next;
    }
    table[ptr].root = temp;
    table[ptr].count++;
    printf("inserted\n");
    return;
}
void searchHash(int data) {
    int hashIndex = data % buckets;
    if(hashIndex < 0){
        hashIndex = hashIndex*-1;
    }
    struct node *temp;
    temp = table[hashIndex].root;
    if (!temp) {
        printf("absent\n");
        return;
    }
    while (temp != NULL) {
        if (temp->data == data) {
            printf("present\n");
            return;
        }
        temp = temp->next;
    }
    printf("absent\n");
    return;
}
int main(int argc, char*argv[]){
    table = malloc(sizeof(struct hash)*buckets);
    FILE *file;
    file = fopen(argv[1],"r");
    if(file == NULL){
        printf("error");
        return 0;
    }
    char num[30];
    while (fgets(num, sizeof(num), file) != NULL) {
        if (num[0] == 'i') {
            insertHash(atoi(&num[1]));
        } else {
            searchHash(atoi(&num[1]));
        }
    }
    return 0;
}
