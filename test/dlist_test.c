// "dlist_test.c"


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <dlist.h>

#define ARRAY_LEN(array)    (sizeof(array) / sizeof(array[0]))

#define TEST_NUM_KEYS       10  
#define TEST_KEY_STR_LEN    32

void **keys_str_random;
void **keys_int_random;

struct dlist str_list;
struct dlist int_list;

struct test
{
    char *name;
    char *description;
    bool (*run)(struct dlist *list, void **keys);
    bool pre_load;
};

DLIST_FUNC_DECL(test,  void)
DLIST_FUNC_CREATE(test, void)

uint64_t test_time_us(void)
{
    struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now)) {
        assert(0);
    }
    return ((uint64_t) now.tv_sec) *1000000 + (uint64_t)(now.tv_nsec / 1000);
}

void **test_keys_alloc(size_t num)
{
    void **keys;

    keys = (void **)calloc(num, sizeof(void *));
    if (!keys) {
        printf("malloc failed\n");
        exit(1);
    }
    return keys;
}

void *test_key_alloc_random_str(void)
{
    size_t i;
    unsigned num;
    char *key;

    key = (char *)malloc(TEST_KEY_STR_LEN + 1);
    if (!key) {
        printf("malloc failed\n");
        exit(1);
    }
    for (i = 0; i < TEST_KEY_STR_LEN; ++i) {
        num = rand();
        num = (num % 96) + 32;    /* ASCII printable only */
        key[i] = (char )num;
    }
    key[TEST_KEY_STR_LEN] = '\0';
    return key;
}
void *test_key_alloc_random_int(void)
{
    uint64_t *key;

    key = (uint64_t *)malloc(sizeof(*key));
    if (!key) {
        printf("malloc failed\n");
        exit(1);
    }
    /* RAND_MAX is not guaranteed to be more than 32K */
    *key = (uint64_t)(rand() & 0xffff) << 48 |
            (uint64_t)(rand() & 0xffff) << 32 |
            (uint64_t)(rand() & 0xffff) << 16 |
            (uint64_t)(rand() & 0xffff);
    return key;
}


void test_keys_generate(void)
{
    size_t i;

    srand(99);    /* Use reproducible random sequences */

    keys_str_random =  test_keys_alloc(TEST_NUM_KEYS + 1);
    keys_int_random =  test_keys_alloc(TEST_NUM_KEYS + 1);
    for (i = 0; i < TEST_NUM_KEYS; ++i) {
        keys_str_random[i] = test_key_alloc_random_str();
        keys_int_random[i] = test_key_alloc_random_int();
    }
    keys_str_random[i] = NULL;
    keys_int_random[i] = NULL;
}

void test_load_keys(struct dlist *list, void **keys)
{
    void **key;
    for (key = keys; *key; ++key) {
        if (!dlist_add(list, *key)) {
            printf("dlist_addt() failed");
            exit(1);
        }
    }
}

void test_reset_list(struct dlist *list)
{
    dlist_reset(list);
}

void test_print_stats(struct dlist *list, const char *label)
{
    printf("Dlist stats: %s\n", label);
    printf("    # entries:           %zu\n", list->num_entries);
    printf("    List size:          %zu\n", dlist_len(list));
}

bool test_run(struct dlist *list, void **keys, 
    const struct test *t)
{
    bool success;
    uint64_t time_us;

    assert(t != NULL);
    assert(t->name != NULL);
    assert(t->run != NULL);

    if (t->pre_load) {
        printf("Pre-loading keys...");
        test_load_keys(list, keys);
        printf("done\n");
    }
    printf("Running...\n");
    time_us = test_time_us();
    success = t->run(list, keys);
    time_us = test_time_us() - time_us;
    if (success) {
        printf("Completed successfully\n");
    } else {
        printf("Failed\n");
    }
    printf("Run time: %llu microseconds\n", (long long unsigned)time_us);
    test_print_stats(list, t->name);
    test_reset_list(list);
    return success;
}

bool test_run_all(struct dlist *list, void **keys, const
        struct test *tests, size_t num_tests, const char *env)
{
    const struct test *t;
    size_t num_failed = 0;

    printf("\n**************************************************\n");
    printf("Starting test series:\n");
    printf("    %s\n", env);
    printf("**************************************************\n\n");
    for (t = tests; t < &tests[num_tests]; ++t) {
        printf("\n**************************************************"
                "\n");
        printf("Test %02u: %s\n", (unsigned)(t - tests) + 1, t->name);
        if (t->description) {
            printf("    Description: %s\n", t->description);
        }
        printf("\n");
        if (!test_run(list, keys, t)) {
            ++num_failed;
        }
    }
    printf("\n**************************************************\n");
    printf("Test results:\n");
    printf("    Passed: %zu\n", num_tests - num_failed);
    printf("    Failed: %zu\n", num_failed);
    printf("**************************************************\n");
    return (num_failed == 0);
}

int test_compare_uint64(const void *a, const void *b)
{
    return *(int64_t *)a - *(int64_t *)b;
}

bool test_add(struct dlist *list, void **keys)
{
    void **key;
    void *data;

    for (key = keys; *key; ++key) {
        data = test_dlist_add(list, *key);
        if (!data) {
            printf("malloc failed\n");
            exit(1);
        }
        if (data != *key) {
            printf("duplicate key found\n");
            return false;
        }
    }
    return true;
}


bool test_get(struct dlist *list, void **keys)
{
    void **key;
    void *data;

    for (key = keys; *key < keys[TEST_NUM_KEYS]; ++key) {
        data = test_dlist_get_data(list, *key);
        if (!data) {
            printf("entry not found\n");
            return false;
        }
        if (data != *key) {
            printf("got wrong entry\n");
            return false;
        }
    }
    return true;
}


bool test_remove(struct dlist *list, void **keys)
{
    void **key;
    void *data;

    for (key = keys; *key < key[TEST_NUM_KEYS]; ++key) {
        data = test_dlist_remove(list, *key);
        if (!data) {
            printf("entry not found\n");
            return false;
        }
        if (data != *key) {
            printf("removed wrong entry\n");
            return false;
        }
    }
    return true;
}


bool test_iterate(struct dlist *list, void **keys)
{
    size_t i = 0;
    struct dlist_iter *iter = dlist_iter(list);

    for (; iter; iter = dlist_iter_next(list, iter)) {
        ++i;
    }
    if (i != TEST_NUM_KEYS) {
        printf("did not iterate through all entries: "
                "observed %zu, expected %u\n", i, TEST_NUM_KEYS);
        return false;
    }
    return true;
}

bool test_iterate_remove(struct dlist *list, void **keys)
{
    size_t i = 0;
    struct dlist_iter *iter = dlist_iter(list);
    void *key;

    while (iter) {
        i++;
        key = test_dlist_iter_get_data(iter);
        if (test_dlist_get_data(list, key) != (key)) {
            printf("invalid iterator on entry #%zu\n", i);
            return false;
        }
        iter = dlist_iter_remove(list, iter);
        if (test_dlist_get_data(list, key) != key) {
            printf("iter_remove failed on entry #%zu\n", i);
            return false;
        }
    }
    if (i != (TEST_NUM_KEYS)) {
        printf("did not iterate through all entries: "
                "observed %zu, expected %u\n", i, TEST_NUM_KEYS);
        return false;
    }
    return true;
}

struct test_foreach_arg {
    struct dlist *list;
    size_t i;
};

int test_foreach_callback(const void *key, void *arg)
{
    struct test_foreach_arg *state = (struct test_foreach_arg *)arg;

    if (state->i & 1) {
        /* Remove every other key */
        test_dlist_remove(state->list, key);
        if (!(test_dlist_remove(state->list, key))) {
            printf("could not remove expected key\n");
            return -1;
        }
    }
    ++state->i;
    return 0;
}

bool test_foreach(struct dlist *list, void **keys)
{
    struct test_foreach_arg arg = { list, 1 };
    size_t size = dlist_len(list);

    if (test_dlist_foreach(list, test_foreach_callback, &arg) < 0) {
        return false;
    }
    if (list->num_entries != size) {
        printf("foreach delete did not remove expected # of entries: "
                "contains %zu vs. expected %zu\n", dlist_len(list),
                size);
        return false;
    }
    return true;
}

bool test_clear(struct dlist *list, void **keys)
{
    dlist_clear(list);
    return true;
}

bool test_reset(struct dlist *list, void **keys)
{
    dlist_reset(list);
    return true;
}

 struct test tests[] = {
        {
                .name = "add performance",
                .description = "add new keys",
                .run = test_add
        },
        {
                .name = "get existing performance",
                .description = "get existing keys",
                .run = test_get,
                .pre_load = true
        },
        {
                .name = "remove performance",
                .description = "remove keys",
                .run = test_remove,
                .pre_load = true
        },
        {
                .name = "iterate performance",
                .description = "iterate through entries",
                .run = test_iterate,
                .pre_load = true
        },
        {
                .name = "iterate remove all",
                .description = "iterate and remove all entries",
                .run = test_iterate_remove,
                .pre_load = true
        },
        {
                .name = "removal in foreach",
                .description = "iterate and delete 1/2 usinglist_foreach",
                .run = test_foreach,
                .pre_load = true
        },
        {
                .name = "clear performance",
                .description = "clear entries",
                .run = test_clear,
                .pre_load = true
        },
        {
                .name = "reset performance",
                .description = "reset entries",
                .run = test_reset,
                .pre_load = true
        }
};

/*
 * Main function
 */
int main(int argc, char **argv)
{
    bool success = true;

    /* Initialize */
    printf("Initializing lists...");
    if (dlist_init(&str_list, dlist_compare_string) < 0) {
        success = false;
    }
    /*
    dlist_set_key_alloc_funcs(&str_list, dlist_alloc_key_string, free);
     */
    if (dlist_init(&int_list, test_compare_uint64) < 0) {
        success = false;
    }
    printf("done\n");

    if (!success) {
        printf("dlist init failed");
        return 1;
    }

    printf("Generating test %u test keys...", TEST_NUM_KEYS);
    test_keys_generate();
    printf("done\n");

    printf("Running tests\n\n");
    success &= test_run_all(&str_list, keys_str_random, tests,
            ARRAY_LEN(tests), "dlist w/randomized string keys");
    success &= test_run_all(&int_list, keys_int_random, tests,
            ARRAY_LEN(tests), "dlist w/randomized integer keys");

    printf("\nTests finished\n");

    dlist_destroy(&str_list);
    dlist_destroy(&int_list);

    if (!success) {
        printf("Tests FAILED\n");
        exit(1);
    }
    return 0;
}
