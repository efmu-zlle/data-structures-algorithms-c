#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 8

typedef struct Node {
    int number;
    struct Node *next;
} Node;

Node *create_node(int num) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("failed to allocated memory");
        exit(EXIT_FAILURE);
    }

    new_node->number = num;
    new_node->next = NULL;
    return new_node;
}

void sorted_insert(Node **bucket, int num) {
    Node *new_node = create_node(num);

    if (*bucket == NULL || num < (*bucket)->number) {
        new_node->next = *bucket;
        *bucket = new_node; 
    } else {
        Node *curr = *bucket; 
        while (curr->next != NULL && curr->next->number < num) {
            curr = curr->next;
        }
        
        new_node->next = curr->next;
        curr->next = new_node;
    }
}

void bucket_sort(int arr[], size_t length) {
    Node *bucket[BUCKET_SIZE] = { NULL };

    for (int i = 0; i < length; i++) {
        int index = arr[i] / BUCKET_SIZE;
        sorted_insert(&bucket[index], arr[i]);
    }

    int k = 0;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        Node *curr = bucket[i];
        while (curr != NULL) {
            arr[k++] = curr->number;
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
    }
}

void print_array(int arr[], size_t length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int array[] = { 6, 1, 2, 5, 4, 3, 7, 8 };
    // int array[] = { 26, 21, 25, 22, 28, 24, 27, 23 };
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("before sorting:\n");
    print_array(array, length);

    bucket_sort(array, length);

    printf("after sorting:\n");
    print_array(array, length);

    return 0;
}