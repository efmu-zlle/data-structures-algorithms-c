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
        printf("shift: no list found\n");
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

    if ((*head)->value == val) {
        Node *next_node = (*head)->next;
        rm_val = (*head)->value;
        free(*head);
        *head = next_node;
        return rm_val;
    }

    Node *prev = *head, *curr = (*head)->next;
    while (curr != NULL) {
        if (curr->value == val) {
            rm_val = curr->value;
            prev->next = curr->next;
            free(curr); 
            curr = NULL;
            return rm_val;
        }
        prev = curr;
        curr = curr->next;
    }

    return rm_val;
}

int delete_by_index(Node **head, int index) {
    int rm_val = -1;
    if (index == 0) {
        Node *next_node = (*head)->next;
        rm_val = (*head)->value;
        free(*head);
        *head = next_node;
        return rm_val;
    }

    Node *curr = *head, *temp_node = NULL;
    for (int i = 0; i < index - 1; i++) {
        if (curr == NULL) {
            return rm_val;
        }
        curr = curr->next;
    }
    
    // if it is NULL then we did not find the value
    // curr->next->next is the value that we want to delete
    if (curr->next == NULL) {
        return rm_val;
    }

    temp_node = curr->next;
    rm_val = temp_node->value;

    curr->next = temp_node->next;

    free(temp_node);
    temp_node = NULL;
    
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

    push_node(&list, 24);
    push_node(&list, 26);
    unshift_node(&list, 28);
    unshift_node(&list, 30);
    push_node(&list, 32);
    push_node(&list, 15);
    print_ll(list);

    printf("shifted: %d\n",shift_node(&list));
    print_ll(list);
    
    printf("popped: %d\n", pop_node(list));
    print_ll(list);

    int deleted;
    if ((deleted = delete_by_value(&list, 24)) == -1) {
        printf("does not exist\n");
    } else {
        printf("value: %d deleted\n", deleted); 
    }
    print_ll(list);

    if ((deleted = delete_by_index(&list, 5)) == -1) {
        printf("does not exist\n");
    } else {
        printf("value: %d deleted\n", deleted); 
    }

    // reverse_ll(&list);
    print_ll(list);

    if (list != NULL) {
        free_node(&list);
    }

    return 0;
}