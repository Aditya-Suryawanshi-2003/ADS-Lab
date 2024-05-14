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

// Non-recursive Inorder Traversal
void inorderNonRecursive(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->key);
        current = current->right;
    }
    printf("\n");
}

// Count leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];

        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }

        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }

    return leafCount;
}

// Mirror the BST
void mirror(struct Node* node) {
    if (node == NULL)
        return;
    else {
        struct Node* temp;

        // Recursively mirror the left and right subtrees
        mirror(node->left);
        mirror(node->right);

        // Swap the pointers
        temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Preorder Traversal (Non-recursive)\n");
        printf("3. Inorder Traversal (Non-recursive)\n");
        printf("4. Display Number of Leaf Nodes\n");
        printf("5. Display Mirror Image\n");
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
                printf("Inorder traversal: ");
                inorderNonRecursive(root);
                break;
            case 4:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                mirror(root);
                printf("Mirror image of the tree (Inorder traversal): ");
                inorderNonRecursive(root);
                mirror(root);  // Re-mirror to restore original structure
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
