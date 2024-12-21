#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INITIAL_SIZE 2
#define LOAD_FACTOR 0.75

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint32_t u64;

typedef int8_t i8;
typedef uint16_t i16;
typedef uint32_t i32;
typedef uint32_t i64;

typedef struct Node {
    u8 *key;
    u32 value; 
    struct Node *next;
} Node;

typedef struct {
    u32 size;
    u32 count;
    Node **bucket;
} HashTable;

u32 hash_key(const char *key, u32 size)  {
    u32 hash = 5381;
    u32 c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return  hash % size;
}

HashTable *create_table(u32 size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->bucket = (Node **)malloc(sizeof(Node *) * size);

    for (u32 i = 0; i < size; i++) {
        table->bucket[i] = NULL;
    }

    return table;
}

void resize_table(HashTable *table) {
    u32 new_size = table->size * 2;
    Node **new_bucket = (Node **)malloc(sizeof(Node *) * new_size);

    for (u32 i = 0; i < new_size; i++) {
        new_bucket[i] = NULL;
    }

    for (u32 i = 0; i < table->size; i++) {
        Node *curr = table->bucket[i];
        while (curr != NULL) {
            u32 index = hash_key(curr->key, new_size);
            Node *next = curr->next;
            curr->next = new_bucket[index];
            new_bucket[index] = curr;
            curr = next;
        }
    }

    free(table->bucket);
    table->bucket = new_bucket;
    table->size = new_size;
}

Node *create_node(u8 *key, u32 value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = NULL;

    return node;
}

void insert(HashTable * table, u8 *key, u32 value) {
    if ((table->count / table->size) > LOAD_FACTOR) {
        resize_table(table);
    }

    u32 index = hash_key(key, table->size);
    Node *curr = table->bucket[index];
    Node *new_node = create_node(key, value);

    if (curr == NULL) {
        table->bucket[index] = new_node;
        table->count++;
        return;
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
    table->count++;
}

i32 find(HashTable *table, u8 *key) {
    u32 index = hash_key(key, table->size);
    Node *curr = table->bucket[index];

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }

    return -1;
}

void delete_key(HashTable *table, u8 *key) {
    u32 index = hash_key(key, table->size);
    Node *curr = table->bucket[index];
    Node *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (prev == NULL) {
                table->bucket[index] = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            table->count--;
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

void free_table(HashTable **table) {
    for (u32 i = 0; i < (*table)->size; i++) {
        Node *curr = (*table)->bucket[i];
        while (curr != NULL) {
            Node *next = curr->next;
            free(curr);
            curr = next;
        }

        (*table)->bucket[i] = NULL;
    }

    free((*table)->bucket);
    free(*table);
    *table = NULL;
} 

void print_table(HashTable *table) {
    for (u32 i = 0; i < table->size; i++) {
        Node *curr = table->bucket[i];
        while (curr != NULL) {
            printf("[%d]: { %s: %d }\n", i, curr->key, curr->value);
            curr = curr->next;
        }
    }
}

int main(void) {
    HashTable *table = create_table(INITIAL_SIZE);

    insert(table, "orange", 10);
    insert(table, "orangi", 30);
    insert(table, "apple", 20);
    insert(table, "banana", 21);
    insert(table, "grape", 40); 
    insert(table, "orango", 40);

    printf("%d\n", find(table, "orange"));
    printf("%d\n", find(table, "watermelon"));

    delete_key(table, "orange");
    printf("%d\n", find(table, "orange"));

    print_table(table);

    free_table(&table);
    return 0;
}