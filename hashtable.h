#ifndef _HASHTABLE_H
#define _HASHTABLE_H



struct hashtable {
    int size;
    int num_entries;
    float load;
    struct list ** bucket; //store list address on every index
    int (*hashf)(void * key, int key_size , int size);
};

struct hashtable_entry{
    void * key;
    void * value;
    int  key_size;
    int  hashed_key;
};

extern struct hashtable * hashtable_create(int size, int(*hashf)(void*, int , int)); // constructor
extern void hashtable_destroy(struct hashtable * ht);
extern void hashtable_put(struct hashtable * ht, char * key, void * data);
extern void hashtable_put_bin(struct hashtable * ht, void * key , int key_size , void * data);
extern void * hashtable_get(struct hashtable * ht, char * key);
extern void  * hashtable_get_bin(struct hashtable * ht, void *key , int key_size);
extern void * hashtable_delete(struct hashtable * ht, char * key);
extern void * hashtable_delete_bin(struct hashtable * ht, void * key, int key_size);
extern void hashtable_for_each(struct hashtable * ht , void(*f)(void * , void *), void * arg);
#endif