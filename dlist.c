#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node node;
struct node{
    int data;
    node* next;
    node* prev;
};

node* node_create(int data,node* next,node* prev){
    node* p = (node*)malloc(sizeof(node));
    p->data = data;
    p->next = next;
    p->prev = prev;
    return p;
}

typedef struct dlist dlist;
struct dlist{
    node* head;
    node* tail;
    size_t size;
};

dlist* dlist_create(){
    dlist* p = (dlist*)malloc(sizeof(dlist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;

    return p;
}

bool dlist_empty(dlist* list){
    return list->size == 0;
}

void checkempty(dlist* list){
    if(dlist_empty(list)){ fprintf(stderr,"list is empty"); exit(1);}
}

size_t dlist_size(dlist* list){
    return list->size;
}


void dlist_addfront_node(dlist* list, node* no){
    //if empty
    //if one
    //if 2 or more
    if(list->size == 0){
        no->next = list->head;
        list->head = no;
        no->prev = NULL;
        list->tail = no;
    }
    else{
        no->next = list->head;
        list->head->prev = no;
        list->head = no;
        no->prev = NULL;
    }
    ++list->size;
}

void dlist_pushfront(dlist* list, int data){
    dlist_addfront_node(list, node_create(data, list ->head,NULL));
}

void dlist_addback_node(dlist* list, node* no){
   if(list->size == 0){
       dlist_addfront_node(list, no); 
    }
    else{
        list->tail->next = no;
        no->prev = list->tail;
        no->next = NULL;
        list->tail = no;
        ++list->size;
    }
}

void dlist_pushback(dlist* list, int data){
    dlist_addback_node(list, node_create(data, NULL, list->tail));
}

void dlist_popfront(dlist* list){
    if (dlist_empty(list)) {
        fprintf(stderr, "Underflow error\n");
        exit(1);
    }
    if(list->size == 1){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    }
    else{
        node* p = list->head->next;
        p->prev = NULL;
        free(list->head);
        list->head = p;
    }
    --list->size;
}
void dlist_popback(dlist* list){
    if (dlist_empty(list)){ fprintf(stderr, "underflow error\n"); exit(1);}
    node* p = list ->head;
    while (p->next != list->tail){
        p = p->next;
    }
    p->next = NULL;
    free(list->tail);
    list->tail = p;
    --list->size;
}

int dlist_front(dlist* list){
    return list->head->data;
}

int dlist_back(dlist* list){
    return list->tail->data;
}


void dlist_clear(dlist* list){
    while(!dlist_empty(list)){
        dlist_popfront(list);
    }
}

void dlist_print(dlist* list, const char* msg){
    checkempty(list);
    printf("%s \n", msg);
    node* p = list->head;
    while(p != NULL)
    {
        printf("previous address: %p ----------current adress: %p ----data: %d----next adress: %p \n",p->prev, p, p->data, p ->next);
        p = p->next;
    }
}

int main(int argc, const char* argv[]){

    dlist_test();

    return 0;
}