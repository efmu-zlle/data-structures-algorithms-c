#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int value;
   struct Node *next; 
} Node;

Node *create_node(int val) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("failed to allocated memory");
        exit(EXIT_FAILURE);
    }

    new_node->value = val;
    new_node->next = NULL;
    return new_node;
}

void push(Node **head, int val) {
    Node *new_node = create_node(val);
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
}

void unshift(Node **head, int val) {
    Node *new_node = create_node(val);
    new_node->next = *head;
    *head = new_node;
}

int main(void) {
    Node *list = NULL; 

    push(&list, 24);
    push(&list, 26);
    unshift(&list, 28);
    unshift(&list, 30);

    return 0;
}