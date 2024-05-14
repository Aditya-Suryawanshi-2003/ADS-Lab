//5.	Write a program to illustrate operations on a BST holding numeric keys. The menu must include: • Insert • Mirror Image • Find • Post order (nonrecursive)


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

// Find a node in the BST
struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return find(root->right, key);

    return find(root->left, key);
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

// Inorder traversal of the BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Non-recursive postorder traversal using two stacks
void postOrderNonRecursive(struct Node* root) {
    if (root == NULL)
        return;

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

int main() {
    struct Node* root = NULL;
    int choice, key;
    struct Node* result;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Mirror Image and Display\n");
        printf("3. Find\n");
        printf("4. Display Postorder (Non-recursive)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                mirror(root);
                printf("Mirror image of the tree (Inorder traversal): ");
                inorder(root);
                printf("\n");
                mirror(root);  // Re-mirror to restore original structure
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                result = find(root, key);
                if (result != NULL)
                    printf("Key %d found in the BST.\n", key);
                else
                    printf("Key %d not found in the BST.\n", key);
                break;
            case 4:
                printf("Postorder traversal: ");
                postOrderNonRecursive(root);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
