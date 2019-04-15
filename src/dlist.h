// "dlist.h"

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdio.h>


/*
 * Macros to declare type-specific versions of dlist_*() functions to
 * allow compile-time type checking and avoid the need for type casting.
 */
#define DLIST_FUNC_DECL(name, data_type)                                \
    data_type name##_dlist_init(struct dlist *list,                     \
        data_type *entry);                                              \
    data_type *name##_dlist_get_data(struct dlist *list,                \
        data_type *entry);                                              \
    data_type *name##_dlist_remove(struct dlist *list,                  \
        const data_type *entry);                                        \
    data_type *name##_dlist_add(struct dlist *list,                     \
        data_type *entry);                                              \
    data_type *name##_dlist_append(struct dlist *tail,                  \
        data_type *entry);                                              \
    data_type *name##_dlist_iter_get_data(struct dlist_iter *iter);     \
                                                                        \
    void name##_dlist_iter_set_data(struct dlist_iter                   \
        *iter, data_type *entry);                                       \
    data_type *name##_dlist_iter_get_key(struct dlist_iter              \
        *iter);                                                         \
                                                                        \
    int name##_dlist_foreach(const struct dlist *list,                  \
        int (*func)(const data_type *, void *), void *arg);                   

#define DLIST_FUNC_CREATE(name, data_type)                              \
    void name##_dlist_init(struct dlist *list,                          \
        data_type *entry)                                               \
    {                                                                   \
        return (data_type) dlist_init(list, (void *) entry);            \
    }                                                                   \
    data_type *name##_dlist_get_data(struct dlist *list,                \
        data_type *entry)                                               \
    {                                                                   \
        return (data_type *) dlist_get_data(list, (void *) entry);      \
    }                                                                   \
    data_type *name##_dlist_remove(struct dlist *list,                  \
        const data_type *entry)                                         \
    {                                                                   \
        return (data_type *) dlist_remove(list,                         \
            (const void *) entry);                                      \
    }                                                                   \
    data_type *name##_dlist_add(struct dlist *list,                     \
        data_type *entry)                                               \
    {                                                                   \
        return (data_type *) dlist_add(list, (void *) entry);           \
    }                                                                   \
     data_type *name##_dlist_append(struct dlist *tail,                 \
        data_type *entry)                                               \
    {                                                                   \
        return (data_type *) dlist_append(tail, (void *) entry);        \
    }                                                                   \
    data_type *name##_dlist_iter_get_data(struct                        \
        dlist_iter *iter)                                               \
    {                                                                   \
        return (data_type *) dlist_iter_get_data(iter);                 \
    }                                                                   \
    void name##_dlist_iter_set_data(struct dlist_iter                   \
    *iter, data_type *entry)                                            \
    {                                                                   \
        dlist_iter_set_data(iter, (void *) entry);                      \
    }                                                                   \
    data_type *name##_dlist_iter_get_key(struct                         \
        dlist_iter *iter)                                               \
    {                                                                   \
        return (data_type *)dlist_iter_get_key(iter);                   \
    }                                                                   \
    struct __##name##_dlist_foreach_state {                             \
        int (*func)(const data_type *, void *);                         \
        void *arg;                                                      \
    };                                                                  \
    static inline int __##name##_dlist_foreach_callback(                \
        const void *data, void *arg)                                    \
    {                                                                   \
        struct __##name##_dlist_foreach_state *s =                      \
            (struct __##name##_dlist_foreach_state *) arg;              \
        return s->func((const data_type *) data, s->arg);               \
    }                                                                   \
    int name##_dlist_foreach(const struct dlist *list,                  \
        int (*func)(const data_type *, void *), void *arg)              \
    {                                                                   \
        struct __##name##_dlist_foreach_state s = {func, arg};          \
        return dlist_foreach(list,                                      \
            __##name##_dlist_foreach_callback, &s);                     \
    }

struct dlist_iter;
struct dlist_node;


/* Linked list State */
struct dlist 
{
    size_t num_entries;
    struct dlist_node *head, *tail;
    int (*key_compare)(const void *, const void *);
    void *(*key_alloc)(void *);
    void (*key_free)(void *);
};


/* List Status */
int dlist_is_empty(struct dlist *list);

size_t dlist_len(struct dlist *list);


/* List Initialization */
int dlist_init(struct dlist *list, int 
    (*key_compare_cb)(const void *, const void *));

void dlist_destroy(struct dlist *list);

/*
 * Enable internal memory management.
 */
void dlist_set_key_alloc_funcs(struct dlist *list,
    void *(*key_alloc_cb)(void *),
    void (*key_free_cb)(void *));


/* Data Modification */
void *dlist_append(struct dlist *list, void *data);

void *dlist_add(struct dlist *list, void *data);

void *dlist_get_data(struct dlist *list, void *data);

void *dlist_remove(struct dlist *list, const void *key);

void dlist_clear(struct dlist *list);

int dlist_reset(struct dlist *list);

/* Iterator */
struct dlist_iter *dlist_iter(const struct dlist *list);

struct dlist_iter *dlist_iter_next(struct dlist *list,
    struct dlist_iter *iter);

struct dlist_iter *dlist_iter_remove(struct dlist *list,
    struct dlist_iter *iter);

void *dlist_iter_get_data(struct dlist_iter *iter);

const void *dlist_iter_get_key(struct dlist_iter *iter);

void dlist_iter_set_data(struct dlist_iter *iter, void *data);



/* Foreach operation */
int dlist_foreach(const struct dlist *list,
    int (*func)(const void *, void *), void *arg);


/* Default Linked List Initialization Key Comparator Func */
int dlist_compare_string(const void *a, const void *b);


/*
 * Default key allocation function for string keys.  Use free() for the
 * key_free_cb.
 */
void *dlist_alloc_key_string(const void *key);




#endif /* __DLIST_H__ */