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

int shift(Node **head) {
    int rm_val = -1;

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

int pop(Node *head) {
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
    
    // if this is true it means that we did not find the value
    // curr->next should have the value that we want to delete
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

void reveser_linked_list(Node *head) {
}

void print_list(Node *head) {
    for (Node *curr = head; curr != NULL; curr = curr->next) {
        printf("[%d]->", curr->value);
    }
    printf("NULL\n");
}

void free_nodes(Node **head) {
    Node *curr = *head;
    while (curr != NULL) {
        Node *temp_node = curr;
        curr = curr->next;
        free(temp_node);
    }

    *head = NULL;
}

int main(void) {
    Node *list = NULL; 

    push(&list, 24);
    push(&list, 26);
    unshift(&list, 28);
    unshift(&list, 30);
    push(&list, 22);

    print_list(list);

    printf("shifted: %d\n",shift(&list));
    print_list(list);
    
    printf("popped: %d\n", pop(list));
    print_list(list);

    int deleted;
    if ((deleted = delete_by_value(&list, 24)) == -1) {
        printf("does not exist\n");
    } else {
        printf("value: %d deleted\n", deleted); 
    }
    print_list(list);

    if ((deleted = delete_by_index(&list, 5)) == -1) {
        printf("does not exist\n");
    } else {
        printf("value: %d deleted\n", deleted); 
    }
    print_list(list);

    if (list != NULL) {
        free_nodes(&list);
    }

    return 0;
}