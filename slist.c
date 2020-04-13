#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node node;
struct node{
    int data;
    node* next;
};

node* node_create(int data,node* next){
    node* p = (node*)malloc(sizeof(node));
    p->data = data;
    p->next = next;
    return p;
}

typedef struct slist slist;
struct slist{
    node* head;
    node* tail;
    size_t size;
};

slist* slist_create(){
    slist* p = (slist*)malloc(sizeof(slist));
    p->head = NULL;
    p->tail = NULL;
    p->size = 0;

    return p;
}

bool slist_empty(slist* list){
    return list->size == 0;
}

void checkempty(slist* list){
    if(slist_empty(list)){ fprintf(stderr,"list is empty");  exit(1);}
}

size_t slist_size(slist* list){
    return list->size;
}


void slist_addfront_node(slist* list, node* no){
    //if empty
    //if one
    //if 2 or more
    no->next = list->head;
    list->head = no;
    if (list->size == 0){ list->tail = no; }
    ++list->size;
}

void slist_pushfront(slist* list, int data){
    slist_addfront_node(list, node_create(data, list ->head));
}

void slist_addback_node(slist* list, node* no){
   if(list->size == 0){
       slist_addfront_node(list, no); 
       return ;
    }
    no->next = NULL;
    list->tail->next = no;
    list->tail = no;
    ++list -> size;
}

void slist_pushback(slist* list, int data){
    slist_addback_node(list, node_create(data, NULL));
}

void slist_popfront(slist* list){
    if (slist_empty(list))
    {
        fprintf(stderr, "Underflow error\n");
        exit(1);
    }
    
    node* p = list->head->next;
    free(list->head);
    list->head = p;
    --list->size;
}

void slist_popback(slist* list){
    if (slist_empty(list)){ fprintf(stderr, "underflow error\n"); exit(1);}
    node* p = list ->head;
    while (p->next != list->tail){
        p = p->next;
    }
    p->next = NULL;
    free(list->tail);
    list->tail = p;
    --list->size;
}

int slist_front(slist* list){
    return list->head->data;
}

int slist_back(slist* list){
    return list->tail->data;
}


void slist_clear(slist* list){
    while(!slist_empty(list)){
        slist_popfront(list);
    }
}

void slist_print(slist* list, const char* msg){
    checkempty(list);
    printf("%s \n", msg);

    node* p = list->head;
    while(p != NULL)
    {
        printf("address of current node: %p ---- %d --> %p\n", p, p->data, p->next);
        p = p->next;
    }
}

int main(int argc, const char* argv[]){

    slist_test();

    return 0;
}