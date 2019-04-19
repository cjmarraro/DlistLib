// "dlist.c"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <dlist.h>

#ifndef DLIST_NOASSERT
#include <assert.h>
#define DLIST_ASSERT(expr)            assert(expr)
#else
#define DLIST_ASSERT(expr)
#endif


struct dlist_node
{
    struct dlist_node *prev, *next;
    void *data;
};

/**** Utility Functions ****/

/* Access pointer to current entry */
static struct dlist_node *dlist_get_entry(const
    struct dlist *list, struct dlist_node *entry)
{  
    struct dlist_node *cur = entry; 
    while (cur->next) {
        return cur;
    }
    return NULL;
}

/* Generic search func for a given key. 
 * Returns NULL if key is invalid.
*/
static struct dlist_node *dlist_find_entry(const struct dlist *list, 
    const void *key)
{
    struct dlist_node *entry = list->head;
    for(; entry; ) 
    {   
        if (list->key_compare(key, entry->data) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}


static void dlist_remove_entry(struct dlist *list, 
     struct dlist_node *del_entry)
{
    struct dlist_node *prev = del_entry->prev;
    struct dlist_node *next = del_entry->next;
    if (list->key_free)  {
        list->key_free(del_entry->data);
    } 

    if (prev) {
        if (next) {
            prev->next = del_entry->next;
            next->prev = del_entry->prev;
        } else {
            prev->next = 0;
            list->tail = del_entry->prev;
        }
    } else {
        if (next) {
            next->prev = 0;
            list->head = del_entry->next;
        } else {
            list->head = 0;
            list->tail = 0;
        }
    }

    free (del_entry);
    list->num_entries--;    
}


static void dlist_free_data(struct dlist *list)
{
    struct dlist_iter *iter;

    if (!list->key_free) return;

    for (iter = dlist_iter(list); iter; 
        iter = dlist_iter_next(list, iter)) 
    {
        list->key_free((void *) dlist_iter_get_data(iter));
    }
}



/**** Initialization ****/
int dlist_init(struct dlist *list, 
    int (*key_compare_cb)(const void *, const void *))
{
    DLIST_ASSERT(list != NULL);

    list->head = list->tail = 0;
    list->num_entries = 0;

    list->head = (struct dlist_node *) calloc(1, 
        sizeof(struct dlist_node));
    
    if (!list->head) return -ENOMEM;

    list->key_compare = key_compare_cb ?
        key_compare_cb : dlist_compare_string;

    list->key_alloc = NULL;
    list->key_free = NULL;
    return 0;
}

void dlist_destroy(struct dlist *list)
{
    if (!list) return;

    dlist_free_data(list);
    free(list->head);
    memset(list, 0, sizeof(*list));
}


/*
 * Enable internal memory management.
 */
void dlist_set_key_alloc_func(struct dlist *list, 
    void *(key_alloc_cb)(void *), void (*key_free_cb)(void *))
{
    DLIST_ASSERT(list != NULL);

    list->key_alloc = key_alloc_cb;
    list->key_free = key_free_cb;
}


/**** Status ****/
int dlist_is_empty(struct dlist *list)
{
    return list->head == NULL ? 1 : 0;
}

size_t dlist_len(struct dlist *list)
{
    DLIST_ASSERT(list != NULL);
    return list->num_entries;
}



/**** Data Modification ****/
void *dlist_get_data(struct dlist *list, void *data)
{
     struct dlist_node *entry;

     DLIST_ASSERT(list != NULL);
     //DLIST_ASSERT(data != NULL);

     entry = dlist_find_entry(list, data);
     if (!entry) return NULL;

     return entry->data;
}

void *dlist_remove(struct dlist *list, const void *key)
{
    struct dlist_node *entry;
    void *data;

    DLIST_ASSERT(list != NULL);
    DLIST_ASSERT(key != NULL);

    entry = dlist_find_entry(list, key);
    if (!entry) 
        return NULL;

    data = entry->data;
    dlist_remove_entry(list, entry);
    return data;
}

void *dlist_append(struct dlist *list,  void *data)
{
    // Initialize Tail Link 
    struct dlist_node *new_node = calloc(1, sizeof(struct dlist_node));
   
    if(!list) {
        fprintf(stderr, "calloc failed. \n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;

    if (list->tail) {
        /* Join the two final nodes together. */
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    } else {
        list->head = new_node;
        list->tail = new_node;
    }
    list->num_entries++;
    return data;  
}

void *dlist_add(struct dlist *list, void *data)
{
     // Initialize Head Link 
    struct dlist_node *new_node;
    new_node = calloc(1, sizeof(struct dlist_node));

    if (!list) {
        fprintf(stderr, "calloc failed. \n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;

    if (list->head) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        list->head = new_node;
        list->tail = new_node;
    }
    list->num_entries++;
    return data;
}

void dlist_clear(struct dlist *list)
{
    DLIST_ASSERT(list);
    dlist_free_data(list);
    list->num_entries = 0;
    memset(list->head, 0, sizeof(struct dlist_node) * (dlist_len(list)));
}

int dlist_reset(struct dlist *list)
{
    dlist_clear(list); 
    dlist_init(list, list->key_compare);
    return 0;
}

/**** Pointer Manipulation ****/
 
/* Get a new linked list iterator. The iterator is 
 * an opaque pointer to dlist_iter_*() functions.
 */
struct dlist_iter *dlist_iter(const struct dlist *list)
{
    DLIST_ASSERT(list != NULL);

    if ((list->num_entries) == 0) return NULL;

    return (struct dlist_iter *) dlist_get_entry(list,
        (list->head));
}

struct dlist_iter *dlist_iter_next(struct dlist *list,
    struct dlist_iter *iter)
{
    struct dlist_node *entry = (struct dlist_node *) iter;

    DLIST_ASSERT(list != NULL);

    if (!iter) return NULL;

    return (struct dlist_iter *) dlist_get_entry(list,
        entry->next);
}

struct dlist_iter *dlist_iter_remove(struct dlist *list,
    struct dlist_iter *iter)
{
    struct dlist_node *entry = (struct dlist_node *) iter;

    DLIST_ASSERT(list != NULL);

    if (!iter) return NULL;  

    if (!entry) 
    /* Iterator is invalid, so just return the next valid entry */
        return dlist_iter_next(list, iter);  
 
    return (struct dlist_iter *) dlist_get_entry(list, entry->next);
        (dlist_remove_entry(list, entry));    
}

const void *dlist_iter_get_key(struct dlist_iter *iter)
{
    if (!iter) {
        return NULL;
    }
    return (void *)((struct dlist_node *)iter)->data;
}

void *dlist_iter_get_data(struct dlist_iter *iter)
{
    if (!iter) return NULL;

    return ((struct dlist_node *) iter)->data;
}

void dlist_iter_set_data(struct dlist_iter *iter,
    void *data)
{
    if (!iter) return;

    ((struct dlist_node *) iter)->data = data;
}


/**** Generic FOREACH caller to user-defined functions ****/
int dlist_foreach(const struct dlist *list,
    int (*func)(const void *, void *), void *arg)
{
    struct dlist_node *entry;
    size_t num_entries;
    const void *data;
    int rc;
    DLIST_ASSERT(list != NULL);
    DLIST_ASSERT(func !=NULL);

    for (entry = &list->head[0]; entry <= &list->head[(list)->num_entries]; ++entry)
    {
        if (!entry->data || !entry->prev) continue;

        num_entries = list->num_entries;
        data = entry->data;
        rc = func(entry->data, arg);
        if (rc < 0) return rc;
        if (rc > 0) return 0;

        if (entry->prev->data != data) {
            --entry;
        } else if (num_entries != list->num_entries) {
            /* Stop immediately if func put/removed another entry */
            return -1;
        }
    }
    return 0;
}


/* Default linked list key-matching callback logic */
int dlist_compare_string(const void *a, const void *b)
{
    return strcmp((const char *) a, (const char *) b);
}

void *dlist_alloc_key_string(const void *key)
{
    return (void *) strdup((const char *) key);
}




// int main()
// {
//     struct dlist myList;
//     dlist_init(&myList, NULL);
    
//     int x = 2;
//     int y =3;
//     dlist_append(&myList, "2");
//     dlist_add(&myList, "3");

//     printf("%ld \n", dlist_len(&myList));
//     void *b = dlist_get_data(&myList, "3");
//     printf("%s \n",(char *)dlist_remove(&myList, "3"));
//     printf("%ld \n", dlist_len(&myList));
    
//     return 0;    
// }

