#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to print tree in level order
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    
    struct Queue {
        struct Node* node;
        struct Queue* next;
    } *front = NULL, *rear = NULL;
    
    struct Queue* enqueue(struct Node* node) {
        struct Queue* temp = (struct Queue*)malloc(sizeof(struct Queue));
        temp->node = node;
        temp->next = NULL;
        if (rear == NULL) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        return front;
    }
    
    struct Node* dequeue() {
        if (front == NULL) return NULL;
        struct Node* temp = front->node;
        struct Queue* tempQueue = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        free(tempQueue);
        return temp;
    }
    
    front = enqueue(root);
    while (front != NULL) {
        struct Node* current = dequeue();
        printf("%d ", current->data);
        if (current->left != NULL) front = enqueue(current->left);
        if (current->right != NULL) front = enqueue(current->right);
    }
    printf("\n");
}

// Function to create the mirror image of the tree
void mirror(struct Node* root) {
    if (root == NULL) return;
    struct Node* temp;
    mirror(root->left);
    mirror(root->right);
    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

// Function to copy the tree
struct Node* copyTree(struct Node* root) {
    if (root == NULL) return NULL;
    struct Node* newNode = createNode(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Function to calculate the height of the tree non-recursively
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;
    
    struct Queue {
        struct Node* node;
        struct Queue* next;
    } *front = NULL, *rear = NULL;
    
    struct Queue* enqueue(struct Node* node) {
        struct Queue* temp = (struct Queue*)malloc(sizeof(struct Queue));
        temp->node = node;
        temp->next = NULL;
        if (rear == NULL) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        return front;
    }
    
    struct Node* dequeue() {
        if (front == NULL) return NULL;
        struct Node* temp = front->node;
        struct Queue* tempQueue = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        free(tempQueue);
        return temp;
    }
    
    front = enqueue(root);
    int height = 0;
    while (1) {
        int nodeCount = 0;
        struct Queue* temp = front;
        while (temp != NULL) {
            nodeCount++;
            temp = temp->next;
        }
        if (nodeCount == 0) return height;
        height++;
        while (nodeCount > 0) {
            struct Node* current = dequeue();
            if (current->left != NULL) front = enqueue(current->left);
            if (current->right != NULL) front = enqueue(current->right);
            nodeCount--;
        }
    }
}

// Main function to test the program
int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Original tree level order traversal:\n");
    levelOrderTraversal(root);
    
    printf("Height of the tree: %d\n", treeHeight(root));
    
    // Displaying mirror image without disturbing the original tree
    struct Node* mirrorRoot = copyTree(root);
    mirror(mirrorRoot);
    printf("Mirror image of the tree (without disturbing the original tree):\n");
    levelOrderTraversal(mirrorRoot);
    
    // Displaying mirror image by disturbing the original tree
    mirror(root);
    printf("Mirror image of the tree (disturbing the original tree):\n");
    levelOrderTraversal(root);

    printf("Original tree level order traversal:\n");
    levelOrderTraversal(root);

    return 0;
}

