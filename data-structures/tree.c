#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int number;
    struct Node *left;
    struct Node *right;
} TreeNode;

TreeNode *create_node(int number) {
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    new_node->number = number;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void insert(TreeNode **root, int number) {
    if (*root == NULL) {
        *root = create_node(number);
    } else {
        if (number <= (*root)->number) {
            insert(&(*root)->left, number);
        } else {
            insert(&(*root)->right, number);
        }
    }
}

int search(TreeNode *root, int number) {
    if (root == NULL) {
        return 0;
    } else if (number < root->number) {
        return search(root->left, number);
    } else if (number > root->number) {
        return search(root->right, number);
    } else {
        return 1;
    }
}

void depth_first_search_pre_order(TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->number);
        depth_first_search_pre_order(root->left);
        depth_first_search_pre_order(root->right);
    }
} 

void depth_first_search_in_order(TreeNode *root) {
    if (root != NULL) {
        depth_first_search_in_order(root->left);
        printf("%d ", root->number);
        depth_first_search_in_order(root->right);
    }
}

void depth_first_search_post_order(TreeNode *root) {
    if (root != NULL) {
        depth_first_search_post_order(root->left);
        depth_first_search_post_order(root->right);
        printf("%d ", root->number);
    }
}

void breadth_first_search(TreeNode *root) {
    TreeNode *queue[64];
    
    int front = 0, rear = 0;

    if (root != NULL) {
        queue[rear++] = root;
    }

    while (front < rear) {
        TreeNode *current = queue[front++];
        printf("%d ", current->number);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }

        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

int tree_sum(TreeNode *root) {
    if (root == NULL) {
        return 0;
    } else {
        int left_sum = tree_sum(root->left);
        int right_sum = tree_sum(root->right);
        return root->number + left_sum + right_sum;
    }
}

TreeNode *delete_node(TreeNode *root, int number) {
    if (root == NULL) {
        return NULL;
    } else if (number < root->number) {
        root->left = delete_node(root->left, number);
    } else if (number > root->number) {
        root->right = delete_node(root->right, number);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            TreeNode *temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            TreeNode *temp = root;
            root = root->left;
            free(temp);
        } else {
            TreeNode *curr = root->left;
            while (curr->right != NULL) {
                curr = curr->right;
            }

            root->number = curr->number;
            root->left = delete_node(root->left, curr->number);
        }
    }

    return root;
}

TreeNode *free_tree(TreeNode **root) {
    if (*root == NULL) {
        return NULL;
    } else {
        free_tree(&(*root)->left);
        free_tree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

int main(void) {
    TreeNode *root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 12);
    insert(&root, 17);
    
    printf("Pre-order: ");
    depth_first_search_pre_order(root); // 10 5 3 7 15 12 17
    printf("\n");
    
    printf("In-order: ");
    depth_first_search_in_order(root); // 3 5 7 10 12 15 17
    printf("\n");

    printf("Post-order: ");
    depth_first_search_post_order(root); // 3 7 5 12 17 15 10
    printf("\n");
    
    printf("Breadth-first: "); // 10 5 15 3 7 12 17
    breadth_first_search(root);
    printf("\n");
    
    printf("Sum: %d\n", tree_sum(root));

    delete_node(root, 10);

    free_tree(&root);

    return 0;
}