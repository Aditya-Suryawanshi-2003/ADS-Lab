#include <stdio.h>
#include <stdlib.h>

// Definition of a node in BST
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a new node in BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    return node;
}

// Function to print level order traversal of BST
void printLevelOrder(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* node = queue[front++];

        printf("%d ", node->key);

        if (node->left != NULL) queue[rear++] = node->left;
        if (node->right != NULL) queue[rear++] = node->right;
    }
}

// Function to create mirror image of BST
void mirror(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* node = queue[front++];

        // Swap left and right children
        struct Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        if (node->left != NULL) queue[rear++] = node->left;
        if (node->right != NULL) queue[rear++] = node->right;
    }
}

// Function to calculate height of BST
int height(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* queue[100];
    int heights[100];
    int front = 0, rear = 0;

    queue[rear] = root;
    heights[rear++] = 1;
    int maxHeight = 0;

    while (front < rear) {
        struct Node* node = queue[front];
        int height = heights[front++];

        if (height > maxHeight) maxHeight = height;

        if (node->left != NULL) {
            queue[rear] = node->left;
            heights[rear++] = height + 1;
        }
        if (node->right != NULL) {
            queue[rear] = node->right;
            heights[rear++] = height + 1;
        }
    }

    return maxHeight;
}

// Function to search a key in BST
struct Node* search(struct Node* root, int key) {
    struct Node* current = root;
    while (current != NULL && current->key != key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

int main() {
    struct Node* root = NULL;
    int keys[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    printf("Levelwise display of BST:\n");
    printLevelOrder(root);
    printf("\n");

    printf("Height of the tree: %d\n", height(root));

    int findKey = 40;
    struct Node* foundNode = search(root, findKey);
    if (foundNode != NULL) {
        printf("Key %d found in the BST.\n", findKey);
    } else {
        printf("Key %d not found in the BST.\n", findKey);
    }

    mirror(root);
    printf("Levelwise display of mirrored BST:\n");
    printLevelOrder(root);
    printf("\n");

    return 0;
}
