//7.	Write a Program to create a Binary Search Tree and perform following nonrecursive operations on it. a. Preorder Traversal b. Postorder Traversal c. Display total Number of Nodes d. Display Leaf nodes.
#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a new node in the BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

// Non-recursive Preorder Traversal
void preorderNonRecursive(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];
        printf("%d ", node->key);

        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
    printf("\n");
}

// Non-recursive Postorder Traversal
void postorderNonRecursive(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[100], * stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    struct Node* node;

    while (top1 >= 0) {
        node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left)
            stack1[++top1] = node->left;
        if (node->right)
            stack1[++top1] = node->right;
    }

    while (top2 >= 0) {
        node = stack2[top2--];
        printf("%d ", node->key);
    }
    printf("\n");
}

// Count total number of nodes
int countNodes(struct Node* root) {
    if (root == NULL) return 0;

    int count = 0;
    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];
        count++;

        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }

    return count;
}

// Display leaf nodes
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];

        if (node->left == NULL && node->right == NULL) {
            printf("%d ", node->key);
        }

        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
    printf("\n");
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Preorder Traversal (Non-recursive)\n");
        printf("3. Postorder Traversal (Non-recursive)\n");
        printf("4. Display Total Number of Nodes\n");
        printf("5. Display Leaf Nodes\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Preorder traversal: ");
                preorderNonRecursive(root);
                break;
            case 3:
                printf("Postorder traversal: ");
                postorderNonRecursive(root);
                break;
            case 4:
                printf("Total number of nodes: %d\n", countNodes(root));
                break;
            case 5:
                printf("Leaf nodes: ");
                displayLeafNodes(root);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
