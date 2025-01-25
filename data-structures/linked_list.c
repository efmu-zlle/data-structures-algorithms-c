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

// push at the end of the list
void push_node(Node **head, int val) {
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

// adds at the beginning of the list
void unshift_node(Node **head, int val) {
    Node *new_node = create_node(val);
    new_node->next = *head;
    *head = new_node;
}

// removes the first element of the list
int shift_node(Node **head) {
    int rm_val = -1;

    // if the list is empty return -1
    if (*head == NULL) {
        printf("shift: no list found\n");
        return rm_val;
    }

    Node *next_node = (*head)->next;
    rm_val = (*head)->value;
    free(*head);
    *head = next_node;

    return rm_val;
}

int pop_node(Node *head) {
    int rm_val = -1;
    
    if (head == NULL) {
        printf("pop: no list found\n");
        return rm_val;
    }

    if (head->next == NULL) {
        rm_val = head->value;
        free(head);
        head = NULL;
        return rm_val;
    }

    Node *curr = head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }

    rm_val = curr->next->value;
    free(curr->next);
    curr->next = NULL;

    return rm_val;
}

int delete_by_value(Node **head, int val) {
    int rm_val = -1;    

    if (*head == NULL) {
        return rm_val;
    }

    if ((*head)->value == val) {
        Node *next = (*head)->next;
        rm_val = (*head)->value;
        free(*head);
        *head = next;
        return rm_val;
    }

    Node *curr = *head, *temp = NULL;
    while (curr->next != NULL && curr->next->value != val) {
        curr = curr->next;
    }

    if (curr->next == NULL) {
        return rm_val;
    }

    temp = curr->next;
    rm_val = temp->value;

    curr->next = temp->next;

    free(temp);
    temp = NULL;

    return rm_val;
}

int delete_by_index(Node **head, int index) {
    int rm_val = -1;

    if (*head == NULL) {
        return rm_val;
    }

    if (index == 0) {
        Node *next = (*head)->next;
        rm_val = (*head)->value;
        free(*head);
        *head = next;
        return rm_val;
    }

    Node *curr = *head, *temp = NULL;
    for (int i = 0; i < index - 1; i++) {
        if (curr->next == NULL) {
            return rm_val;
        }
        curr = curr->next;
    }

    if (curr->next == NULL) {
        return rm_val;
    }

    temp = curr->next;
    rm_val = temp->value;

    curr->next = temp->next;

    free(temp);
    temp = NULL;

    return rm_val;
}

// reverse the linked list
void reverse_ll(Node **head) {
    Node *prev = NULL,
        *curr = *head,
        *next = NULL;
    
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
}

// print the linked list
void print_ll(Node *head) {
    for (Node *curr = head; curr != NULL; curr = curr->next) {  
        printf("[%d]->", curr->value);
    }
    printf("NULL\n");
}

// free the linked list
void free_node(Node **head) {
    if (*head == NULL) {
        return;
    }

    free_node(&(*head)->next);
    free(*head);
    *head = NULL;
}

int main(void) {
    Node *list = NULL;

    push_node(&list, 3);
    push_node(&list, 4);
    push_node(&list, 5);
    unshift_node(&list, 1);
    push_node(&list, 6);

    print_ll(list); // [1]->[3]->[4]->[5]->[6]->NULL

    // printf("shift: %d\n", shift_node(&list)); // 1
    // print_ll(list); // [3]->[4]->[5]->[6]->NULL

    // printf("pop: %d\n", pop_node(list)); // 6
    // print_ll(list); // [3]->[4]->[5]->NULL

    // printf("delete by value: %d\n", delete_by_value(&list, 7)); // -1
    // print_ll(list); // [1]->[3]->[5]->[6]->NULL 

    printf("delete by index: %d\n", delete_by_index(&list, 5));  
    print_ll(list); // [3]->[5]->NULL

    // reverse_ll(&list);
    // print_ll(list); // [5]->[3]->NULL

    free_node(&list);
    list = NULL;

    return 0;
}
