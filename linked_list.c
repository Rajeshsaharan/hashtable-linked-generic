#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


//constructor 
struct list * list_create(){
    struct list * list =  malloc(sizeof(struct list));
    if(list == NULL){
        printf("%s\n", "list is not initlized");
        return list;
    }
    list->count = 0;
    list->head = NULL;
    return list;
}


//destroy the list
void list_distroy(struct list * list){
    struct node * current = list->head;
    while(current){
        struct node * temp =current->next;
        free(current);
        current = temp;
    }
    free(list);
}

void list_insert(struct list * list, void * data){
    //adding at the head of list
    struct node * new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL){
        printf("%s\n", "new node is not init");
        return;
    }
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node; //this will update list head 
    list->count++;
}

//append list at the back

void list_append(struct list *list, void * data){
    struct node * head = list->head;
    struct node * new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL){
        printf("%s\n", "new node is not init");
        return;
    }
    if(head == NULL){
        return list_insert(list, data);
    }
    while(head->next){
        head = head->next;
    }
    new_node->data = data;
    head->next = new_node;
    new_node->next = NULL;
    list->count++;
    //head is the same 
}

void * list_head(struct list * list){
    return list->head->data;
}
void * list_tail(struct list * list){
    struct node * head = list->head;
    while(head){
        head = head->next;
    }
    return head->data;
}


//finding some data in list
void * list_find(struct list * list, void * data, int (*compare_function)(void *, void *)){
    struct node * head = list->head;
    //head can be null if list is empty
    if(head == NULL){
        return NULL;
    }
    while(head){
        if(compare_function(data, head->data)== 0){ //com
            break;
        }
        head = head->next;
    }
    if(head == NULL){
        return NULL;
    }
    return head->data; // if we find the given data in the list
}


void * list_delete(struct list * list, void * data, int (*compare_function)(void * , void *)){
    struct node * head = list->head, * prev = NULL;
    if(head == NULL){
        return NULL;
    }
    while(head){
        if(compare_function(data, head->data)== 0){
            //means we found out data
            if(prev == NULL){
                //means we get head data matching so
                struct node * next= head->next;
                free(head);
                list->head = next;
                return data;
            }else{
                prev->next = head->next;
                free(head);
                return data;
            }
        }
        list->count--;
        prev = head;
        head = head->next;
    }
    //if loop complete without finding data for its parameter
    if(head == NULL){
        return NULL;
    }
    return NULL;
}

int  list_count(struct list * list){
    return list->count;
}

void list_for_each(struct list * list, void(* f)(void *, void *), void * arg){
    struct node * head = list->head;
    while(head){
        f(head->data, arg);
        head = head->next;
    }
}
void ** list_to_array(struct list * list){
    void ** array = calloc(list->count+1, sizeof(void *));
    int i =0;
    struct node * head = list->head;
    while(head){
        array[i] = head->data;
        head = head->next;
        i++;
            }
    return array;
}
void list_array_free(void ** array){
    free(array);
}