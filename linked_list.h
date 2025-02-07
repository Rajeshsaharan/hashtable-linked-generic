#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


//struct for linked list head and count for size

struct list{
    struct node * head;
    int count;
};
struct node{
    void * data;
    struct node * next;
};


extern struct list * list_create(void); // constructor
extern void list_distroy(struct list * list); //destroy the list all
extern void list_insert(struct list * list, void * data);
extern void list_append(struct list * list, void* data); // append data at back
extern void * list_head(struct list * list); // retrun the head of list [can be any type] thats why we use void *
extern void * list_tail(struct list * list); // return the tail of list
extern void * list_find(struct list * list, void * data, int(*compare_function)(void *, void *));
extern void * list_delete(struct list * list, void * data, int(*compare_function)(void *, void *));
extern int list_count(struct list * list);
extern void list_for_each(struct list * list, void(*f)(void * , void *), void * arg); // for each every item;
extern void ** list_to_array(struct list * list);
extern void list_array_free(void ** arr);

#endif