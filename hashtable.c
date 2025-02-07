#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "linked_list.h"

#define SIZE 128

void add_entry_count(struct hashtable * ht , int count){
    ht->num_entries += count;
    
}

int default_hash(void * key, int key_size, int size){
    const int R = 31;
    int h =0;
    unsigned char * p = key;
    int i =0;
    while(i < key_size){
        h = (R + h + p[i]) % size;
        i++;
    }
    return h;
}

//constructor 

struct hashtable * hashtable_create(int size, int(hashf)(void *,  int, int)){
    struct hashtable * ht = malloc(sizeof(struct hashtable));
    if(ht == NULL){
        printf("%s\n", "hashtable cant created now");
        return ht;
    }
    if(size <1){
        //means user didn't specify user
        size = SIZE;
    }
    if(hashf == NULL){
        hashf = default_hash; // if hash isn't defined
    }
    ht->size = size;
    ht->hashf = hashf;
    ht->num_entries = 0;
    ht->load = 0;
    ht->bucket = malloc(size * sizeof(struct list *));
    int i =0;
    while(i < size){
        ht->bucket[i] = list_create(); //create space for linked list 
        i++;
    }
    return ht;
}

//free the hashtable
void hashtable_entry_free(void * hashtable_entry, void * arg){
    free(hashtable_entry);
}

void hashtable_destroy(struct hashtable * ht){
    int i =0;
    while(i < ht->size){
        struct list * list = ht-> bucket[i];
        list_for_each(list, hashtable_entry_free, NULL); //free hashtable entry as data
        i++;
        free(list);
    }
    free(ht);
}

void hashtable_put(struct hashtable *ht, char * key , void * data){
    return hashtable_put_bin(ht,key,strlen(key), data);
}



void hashtable_put_bin(struct hashtable * ht, void * key, int key_size, void * data){
    int index = ht->hashf(key,key_size,ht->size);
    struct list * list = ht->bucket[index];
    
    struct hashtable_entry * entry = malloc(sizeof(struct hashtable_entry));
    if(entry == NULL){
        printf("%s\n", "hashtable entery cant be make");
        return;
    }
    
    entry->hashed_key = index;
    entry->value = data;
    entry->key_size = key_size;
    entry->key = malloc(key_size);
    memcpy(entry->key, key, key_size);

    list_append(list, entry);
    
}

void * hashtable_get(struct hashtable * ht, char * key){
    return hashtable_get_bin(ht,key, strlen(key));
}


//for comparing the data
int hashtable_entry_compare(void * a, void *  b){
    struct hashtable_entry * data1 = a;
    struct hashtable_entry * data2 = b;
    int size1 = data1->key_size;
    int size2 = data2->key_size;
    if(size1 - size2){
        return size1-size2 ; //means both data have key same size cant be 0;
    }
    return memcmp(data1->key,data2->key, size1); // also can be used size2;

}


void  * hashtable_get_bin(struct hashtable * ht,void * key, int key_size){
        int index = ht->hashf(key,key_size, ht->size);
        struct list * list = ht->bucket[index];
        struct hashtable_entry *  comparison_data = malloc(sizeof(struct hashtable_entry));
        comparison_data->key = key;
        comparison_data->key_size = key_size;
        struct hashtable_entry * hashtable_entry = list_find(list, comparison_data, hashtable_entry_compare);
        if(hashtable_entry == NULL){
            return NULL;
        }
        return hashtable_entry->value;
} 

void * hashtable_delete(struct hashtable * ht, char * key){
    return hashtable_delete_bin(ht, key, strlen(key));
}

void * hashtable_delete_bin(struct hashtable * ht, void * key, int key_size){
    int index = ht->hashf(key, key_size, ht->size);
    struct list * list = ht->bucket[index];
    struct hashtable_entry *  comparison_data = malloc(sizeof(struct hashtable_entry));
        comparison_data->key = key;
        comparison_data->key_size = key_size;
    struct hashtable_entry * hashtable_entry = list_delete(list,comparison_data, hashtable_entry_compare);
    if(hashtable_entry == NULL){
        return NULL;
    }
    return hashtable_entry->value;
}
