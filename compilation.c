//1.	Write a Program to create a Binary Tree and perform following nonrecursive operations on it. a. Preorder Traversal, b. Postorder Traversal, c. Count total no. of nodes, d. Display height of a tree.

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Stack structure for iterative traversal
struct Stack {
    struct Node* node;
    struct Stack* next;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to push an element to the stack
void push(struct Stack** top, struct Node* node) {
    struct Stack* newStackNode = (struct Stack*)malloc(sizeof(struct Stack));
    newStackNode->node = node;
    newStackNode->next = *top;
    *top = newStackNode;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* top) {
    return top == NULL;
}

// Function to pop an element from the stack
struct Node* pop(struct Stack** top) {
    if (isEmpty(*top)) {
        printf("Stack is empty\n");
        return NULL;
    } else {
        struct Stack* temp = *top;
        struct Node* node = temp->node;
        *top = (*top)->next;
        free(temp);
        return node;
    }
}

// Function for non-recursive Preorder Traversal
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Stack* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct Node* node = pop(&stack);
        printf("%d ", node->data);

        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
}

// Function for non-recursive Postorder Traversal
void postorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Stack* stack1 = NULL;
    struct Stack* stack2 = NULL;
    push(&stack1, root);

    while (!isEmpty(stack1)) {
        struct Node* node = pop(&stack1);
        push(&stack2, node);

        if (node->left) push(&stack1, node->left);
        if (node->right) push(&stack1, node->right);
    }

    while (!isEmpty(stack2)) {
        struct Node* node = pop(&stack2);
        printf("%d ", node->data);
    }
}

// Function to count the total number of nodes
int countNodes(struct Node* root) {
    if (root == NULL) return 0;

    int count = 0;
    struct Stack* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct Node* node = pop(&stack);
        count++;

        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
    return count;
}

// Function to display the height of the tree
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;

    int height = 0;
    struct Stack* stack = NULL;
    struct Stack* levelStack = NULL;
    push(&stack, root);
    push(&levelStack, (struct Node*)(long)1);

    while (!isEmpty(stack)) {
        struct Node* node = pop(&stack);
        int level = (int)(long)pop(&levelStack);

        if (level > height) height = level;

        if (node->right) {
            push(&stack, node->right);
            push(&levelStack, (struct Node*)(long)(level + 1));
        }
        if (node->left) {
            push(&stack, node->left);
            push(&levelStack, (struct Node*)(long)(level + 1));
        }
    }
    return height;
}

// Main function to test the program
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    int totalNodes = countNodes(root);
    printf("Total number of nodes: %d\n", totalNodes);

    int height = treeHeight(root);
    printf("Height of the tree: %d\n", height);

    return 0;
}



//2.	Write a Program to create a Binary Tree and perform following nonrecursive operations on it. a. inorder Traversal; b. Count no. of nodes on longest path; c. display tree levelwise; d. Display height of a tree.

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Queue structure for level order traversal
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

// Queue for level order traversal
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a new queue node
struct QueueNode* createQueueNode(struct Node* treeNode) {
    struct QueueNode* newQueueNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;
    return newQueueNode;
}

// Function to create a queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to enqueue an element
void enqueue(struct Queue* queue, struct Node* treeNode) {
    struct QueueNode* newQueueNode = createQueueNode(treeNode);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newQueueNode;
        return;
    }
    queue->rear->next = newQueueNode;
    queue->rear = newQueueNode;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to dequeue an element
struct Node* dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    struct Node* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

// Function to display the tree level-wise
void displayLevelwise(struct Node* root) {
    if (root == NULL) return;

    struct Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        int nodeCount = 0;
        struct Queue* tempQueue = createQueue();
        while (!isQueueEmpty(queue)) {
            struct Node* current = dequeue(queue);
            printf("%d ", current->data);

            if (current->left) {
                enqueue(tempQueue, current->left);
            }
            if (current->right) {
                enqueue(tempQueue, current->right);
            }
        }

        while (!isQueueEmpty(tempQueue)) {
            enqueue(queue, dequeue(tempQueue));
        }
        free(tempQueue);

        printf("\n");
    }
}

// Stack structure for iterative traversal
struct Stack {
    struct Node* node;
    struct Stack* next;
};

// Function to push an element to the stack
void push(struct Stack** top, struct Node* node) {
    struct Stack* newStackNode = (struct Stack*)malloc(sizeof(struct Stack));
    newStackNode->node = node;
    newStackNode->next = *top;
    *top = newStackNode;
}

// Function to check if the stack is empty
int isEmptyStack(struct Stack* top) {
    return top == NULL;
}

// Function to pop an element from the stack
struct Node* pop(struct Stack** top) {
    if (isEmptyStack(*top)) {
        printf("Stack is empty\n");
        return NULL;
    } else {
        struct Stack* temp = *top;
        struct Node* node = temp->node;
        *top = (*top)->next;
        free(temp);
        return node;
    }
}

// Function for non-recursive Inorder Traversal
void inorderTraversal(struct Node* root) {
    struct Stack* stack = NULL;
    struct Node* current = root;

    while (current != NULL || !isEmptyStack(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to display the height of the tree
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;

    int height = 0;
    struct Stack* stack = NULL;
    struct Stack* levelStack = NULL;
    push(&stack, root);
    push(&levelStack, (struct Node*)(long)1);

    while (!isEmptyStack(stack)) {
        struct Node* node = pop(&stack);
        int level = (int)(long)pop(&levelStack);

        if (level > height) height = level;

        if (node->right) {
            push(&stack, node->right);
            push(&levelStack, (struct Node*)(long)(level + 1));
        }
        if (node->left) {
            push(&stack, node->left);
            push(&levelStack, (struct Node*)(long)(level + 1));
        }
    }
    return height;
}

// Function to count the number of nodes on the longest path
int countNodesOnLongestPath(struct Node* root) {
    return treeHeight(root);
}

// Main function to test the program
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Tree Level-wise:\n");
    displayLevelwise(root);
    printf("\n");

    int longestPathNodes = countNodesOnLongestPath(root);
    printf("Number of nodes on the longest path: %d\n", longestPathNodes);

    int height = treeHeight(root);
    printf("Height of the tree: %d\n", height);

    return 0;
}


//3.	Write a Program to create a Binary Search Tree holding numeric keys and perform following nonrecursive operations on it. a. Levelwise display, b. Mirror image, c. Display height of a tree, d. Find 

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

// // Function to calculate height of BST
// int height(struct Node* root) {
//     if (root == NULL) return 0;

//     struct Node* queue[100];
//     int heights[100];
//     int front = 0, rear = 0;

//     queue[rear] = root;
//     heights[rear++] = 1;
//     int maxHeight = 0;

//     while (front < rear) {
//         struct Node* node = queue[front];
//         int height = heights[front++];

//         if (height > maxHeight) maxHeight = height;

//         if (node->left != NULL) {
//             queue[rear] = node->left;
//             heights[rear++] = height + 1;
//         }
//         if (node->right != NULL) {
//             queue[rear] = node->right;
//             heights[rear++] = height + 1;
//         }
//     }

//     return maxHeight;
// }

int max(int a , int b){
    if(a >= b){
        return a;
    }else{
        return b ;
    }
}

int height(struct Node * root){
    if(root == NULL) return 0;

    return 1+ max(height(root->left),height(root->right));
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


//4.	Write a program to illustrate operations on a BST holding numeric keys. The menu must include: • Insert • Delete • Find • display in Inorder way

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

// Find the minimum value node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Delete a node in the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Find a node in the BST
struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return find(root->right, key);

    return find(root->left, key);
}

// Inorder traversal of the BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    struct Node* result;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Find\n");
        printf("4. Display in Inorder\n");
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
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
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
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}


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

//6.	Write a Program to create a Binary Search Tree and perform following nonrecursive operations on it. a. Preorder Traversal b. Inorder Traversal c. Display Number of Leaf Nodes d. Mirror Image
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






//8.	Write a Program to create a Binary Search Tree and perform deletion of a node from it. Also display the tree in nonrecursive postorder way.
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

// Function to find the minimum value node in the tree
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Stack structure for non-recursive traversal
struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

// Function to create a stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an item onto the stack
void push(struct Stack* stack, struct Node* item) {
    stack->array[++stack->top] = item;
}

// Function to pop an item from the stack
struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->array[stack->top--];
}

// Function for non-recursive postorder traversal
void postOrderNonRecursive(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack(100);
    struct Stack* out = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        struct Node* curr = pop(stack);
        push(out, curr);
        if (curr->left) {
            push(stack, curr->left);
        }
        if (curr->right) {
            push(stack, curr->right);
        }
    }
    while (!isEmpty(out)) {
        printf("%d ", pop(out)->data);
    }
    printf("\n");
    free(stack->array);
    free(stack);
    free(out->array);
    free(out);
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

    printf("Postorder traversal of the given tree:\n");
    postOrderNonRecursive(root);

    printf("Deleting 20\n");
    root = deleteNode(root, 20);
    printf("Postorder traversal after deletion:\n");
    postOrderNonRecursive(root);

    printf("Deleting 30\n");
    root = deleteNode(root, 30);
    printf("Postorder traversal after deletion:\n");
    postOrderNonRecursive(root);

    printf("Deleting 50\n");
    root = deleteNode(root, 50);
    printf("Postorder traversal after deletion:\n");
    postOrderNonRecursive(root);

    return 0;
}




//9.	Write a Program to create a Binary Search Tree and display it levelwise. Also perform deletion of a node from it.
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

// Function to find the minimum value node in the tree
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Queue structure for level order traversal
struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct Node** array;
};

// Function to create a queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

// Function to check if the queue is full
int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Function to add an item to the queue
void enqueue(struct Queue* queue, struct Node* item) {
    if (isFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from the queue
struct Node* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    struct Node* item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function for level order traversal
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Queue* queue = createQueue(100);
    enqueue(queue, root);
    while (!isEmpty(queue)) {
        struct Node* node = dequeue(queue);
        printf("%d ", node->data);
        if (node->left != NULL) {
            enqueue(queue, node->left);
        }
        if (node->right != NULL) {
            enqueue(queue, node->right);
        }
    }
    printf("\n");
    free(queue->array);
    free(queue);
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

    printf("Level order traversal of the given tree:\n");
    levelOrderTraversal(root);

    printf("Deleting 20\n");
    root = deleteNode(root, 20);
    printf("Level order traversal after deletion:\n");
    levelOrderTraversal(root);

    printf("Deleting 30\n");
    root = deleteNode(root, 30);
    printf("Level order traversal after deletion:\n");
    levelOrderTraversal(root);

    printf("Deleting 50\n");
    root = deleteNode(root, 50);
    printf("Level order traversal after deletion:\n");
    levelOrderTraversal(root);

    return 0;
}





//10.	Write a Program to create a Binary Search Tree and display its mirror image with and without disturbing the original tree. Also display height of a tree using nonrecursion.
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






//11.	Write a program to efficiently search a particular employee record by using Tree data structure. Also sort the data on emp-id in ascending order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an employee
typedef struct Employee {
    int emp_id;
    char name[100];
    struct Employee *left, *right;
} Employee;

// Function to create a new employee node
Employee* createEmployee(int emp_id, char* name) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert a new employee into the BST
Employee* insertEmployee(Employee* root, int emp_id, char* name) {
    if (root == NULL) return createEmployee(emp_id, name);
    
    if (emp_id < root->emp_id)
        root->left = insertEmployee(root->left, emp_id, name);
    else if (emp_id > root->emp_id)
        root->right = insertEmployee(root->right, emp_id, name);
    
    return root;
}

// Function to search for an employee by emp_id
Employee* searchEmployee(Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) return root;
    
    if (emp_id < root->emp_id)
        return searchEmployee(root->left, emp_id);
    else
        return searchEmployee(root->right, emp_id);
}

// In-order traversal to print employees in ascending order of emp_id
void inOrderTraversal(Employee* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Employee ID: %d, Name: %s\n", root->emp_id, root->name);
        inOrderTraversal(root->right);
    }
}

// Main function
int main() {
    Employee* root = NULL;
    root = insertEmployee(root, 102, "Alice");
    root = insertEmployee(root, 101, "Bob");
    root = insertEmployee(root, 104, "Charlie");
    root = insertEmployee(root, 103, "David");
    
    printf("Employees in ascending order of emp_id:\n");
    inOrderTraversal(root);

    int emp_id_to_search = 103;
    Employee* searchedEmployee = searchEmployee(root, emp_id_to_search);
    if (searchedEmployee != NULL) {
        printf("Employee found: ID: %d, Name: %s\n", searchedEmployee->emp_id, searchedEmployee->name);
    } else {
        printf("Employee with ID %d not found.\n", emp_id_to_search);
    }

    return 0;
}






//12.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Preorder way.
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in an Inorder Threaded Binary Tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread; // True if left pointer is a thread
    int rthread; // True if right pointer is a thread
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1; // Initial threads
    return newNode;
}

// Insert a new node in the Inorder Threaded Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL)
        return newNode;

    Node* parent = NULL;
    Node* current = root;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            if (current->lthread == 0)
                current = current->left;
            else
                break;
        } else {
            if (current->rthread == 0)
                current = current->right;
            else
                break;
        }
    }

    if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rthread = 0;
        parent->right = newNode;
    }

    return root;
}

// Function to find the inorder successor of a given node
Node* inorderSuccessor(Node* ptr) {
    if (ptr->rthread == 1)
        return ptr->right;

    ptr = ptr->right;
    while (ptr->lthread == 0)
        ptr = ptr->left;

    return ptr;
}

// Function to traverse the threaded binary tree in preorder
void preorderTraversal(Node* root) {
    if (root == NULL)
        return;

    Node* current = root;
    while (current != NULL) {
        // Visit the node
        printf("%d ", current->data);

        // If left is not a thread, move to the left child
        if (current->lthread == 0) {
            current = current->left;
        } else {
            // If right is not a thread, move to the right child
            while (current->rthread == 1 && current->right != NULL)
                current = current->right;
            current = current->right;
        }
    }
}

// Main function
int main() {
    Node* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    printf("Preorder traversal of the Inorder Threaded Binary Tree:\n");
    preorderTraversal(root);

    return 0;
}







//13.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Inorder way.
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in an Inorder Threaded Binary Tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread; // True if left pointer is a thread
    int rthread; // True if right pointer is a thread
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1; // Initial threads
    return newNode;
}

// Insert a new node in the Inorder Threaded Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL)
        return newNode;

    Node* parent = NULL;
    Node* current = root;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            if (current->lthread == 0)
                current = current->left;
            else
                break;
        } else {
            if (current->rthread == 0)
                current = current->right;
            else
                break;
        }
    }

    if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rthread = 0;
        parent->right = newNode;
    }

    return root;
}

// Function to find the inorder successor of a given node
Node* inorderSuccessor(Node* ptr) {
    if (ptr->rthread == 1)
        return ptr->right;

    ptr = ptr->right;
    while (ptr->lthread == 0)
        ptr = ptr->left;

    return ptr;
}

// Function to traverse the threaded binary tree in inorder
void inorderTraversal(Node* root) {
    if (root == NULL)
        return;

    // Go to the leftmost node
    Node* current = root;
    while (current->lthread == 0)
        current = current->left;

    while (current != NULL) {
        printf("%d ", current->data);
        current = inorderSuccessor(current);
    }
}

// Main function
int main() {
    Node* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    printf("Inorder traversal of the Inorder Threaded Binary Tree:\n");
    inorderTraversal(root);

    return 0;
}






//14.	Write a Program to implement AVL tree and perform different rotations on it and display it in sorted manner.
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in an AVL tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int height;
} Node;

// Function to get the height of the tree
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of node N
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a node in the AVL tree and perform necessary rotations
Node* insert(Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal data is not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Inorder traversal of the AVL tree
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Main function
int main() {
    Node* root = NULL;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Inorder traversal of the constructed AVL tree is:\n");
    inorderTraversal(root);

    return 0;
}





//15.	Write a Program to implement AVL tree and perform deletion on it and display it in sorted manner.
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in an AVL tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int height;
} Node;

// Function to get the height of the tree
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of node N
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a node in the AVL tree and perform necessary rotations
Node* insert(Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal data is not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to find the node with the smallest value (leftmost leaf)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node from the AVL tree and perform necessary rotations
Node* deleteNode(Node* root, int data) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the data to be deleted is smaller than the root's data, then it lies in left subtree
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    // If the data to be deleted is greater than the root's data, then it lies in right subtree
    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    // If data is same as root's data, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal of the AVL tree
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Main function
int main() {
    Node* root = NULL;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Inorder traversal of the constructed AVL tree is:\n");
    inorderTraversal(root);
    printf("\n");

    // Delete nodes from the AVL tree
    root = deleteNode(root, 10);
    root = deleteNode(root, 20);

    printf("Inorder traversal of the AVL tree after deletion is:\n");
    inorderTraversal(root);

    return 0;
}




//16.	Write a Program to accept a graph from user and represent it with Adjacency Matrix and perform BFS and DFS traversals on it.
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;
int n; // Number of vertices

void addEdge(int start, int end) {
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1; // Assuming it's an undirected graph
}

void createGraph() {
    int i, j, edges, start, end;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge (start end): ");
        scanf("%d %d", &start, &end);
        addEdge(start, end);
    }
}

void bfs(int start) {
    int i;
    front = rear = 0;
    queue[rear] = start;
    visited[start] = 1;

    while (front <= rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (i = 0; i < n; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

void dfs(int start) {
    int i;
    printf("%d ", start);
    visited[start] = 1;

    for (i = 0; i < n; i++) {
        if (adjMatrix[start][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

void resetVisited() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

int main() {
    int startVertex;

    createGraph();

    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    resetVisited();
    printf("BFS traversal starting from vertex %d: ", startVertex);
    bfs(startVertex);
    printf("\n");

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    resetVisited();
    printf("DFS traversal starting from vertex %d: ", startVertex);
    dfs(startVertex);
    printf("\n");

    return 0;
}





//17.	Write a Program to accept a graph from user and represent it with Adjacency List and perform BFS and DFS traversals on it.
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

Node* createNode(int vertex) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void bfs(Graph* graph, int startVertex) {
    int queue[MAX];
    int front = 0;
    int rear = -1;

    graph->visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                queue[++rear] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

void dfs(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            dfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int vertices, edges, startVertex, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (start end): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    resetVisited(graph);
    printf("BFS traversal starting from vertex %d: ", startVertex);
    bfs(graph, startVertex);
    printf("\n");

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    resetVisited(graph);
    printf("DFS traversal starting from vertex %d: ", startVertex);
    dfs(graph, startVertex);
    printf("\n");

    return 0;
}




//18.	Write a Program to implement Prim’s algorithm to find minimum spanning tree of a user defined graph. Use Adjacency Matrix to represent a graph.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int adjMatrix[MAX][MAX];
int n; // Number of vertices

void createGraph() {
    int i, j, edges, start, end, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = INF;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge (start end weight): ");
        scanf("%d %d %d", &start, &end, &weight);
        adjMatrix[start][end] = weight;
        adjMatrix[end][start] = weight; // Assuming it's an undirected graph
    }
}

int minKey(int key[], int mstSet[]) {
    int min = INF, minIndex;

    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], minIndex = v;

    return minIndex;
}

void printMST(int parent[]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d \n", parent[i], i, adjMatrix[i][parent[i]]);
}

void primMST() {
    int parent[MAX]; // Array to store constructed MST
    int key[MAX];    // Key values used to pick minimum weight edge in cut
    int mstSet[MAX]; // To represent set of vertices not yet included in MST

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (adjMatrix[u][v] && mstSet[v] == 0 && adjMatrix[u][v] < key[v]) {
                parent[v] = u, key[v] = adjMatrix[u][v];
            }
    }

    printMST(parent);
}

int main() {
    createGraph();
    primMST();
    return 0;
}





//21.	WAP to implement Heap sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks), with key as student_roll_no. And count the number of swap performed.
#include <stdio.h>
#include <string.h>

// Define the Student structure
typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

int swap_count = 0; // Global variable to count the number of swaps

// Function to merge two halves
void merge(Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            swap_count += (n1 - i); // Increment swap count by the number of remaining elements in L[]
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(Student arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to print the array
void printArray(Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Roll No: %d, Total Marks: %d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

// Main function
int main() {
    Student arr[] = {
        {"Alice", 5, 85},
        {"Bob", 2, 75},
        {"Charlie", 8, 95},
        {"David", 1, 65},
        {"Eve", 7, 80}
    };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is:\n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is:\n");
    printArray(arr, arr_size);

    printf("\nNumber of swaps performed: %d\n", swap_count);
    return 0;
}





//22.	WAP to convert a given Infix expression into its equivalent Postfix expression and evaluate it using stack.
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Stack structure for characters
typedef struct {
    int top;
    unsigned capacity;
    char* array;
} CharStack;

// Stack structure for integers
typedef struct {
    int top;
    unsigned capacity;
    int* array;
} IntStack;

// Function to create a stack of given capacity for characters
CharStack* createCharStack(unsigned capacity) {
    CharStack* stack = (CharStack*) malloc(sizeof(CharStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to create a stack of given capacity for integers
IntStack* createIntStack(unsigned capacity) {
    IntStack* stack = (IntStack*) malloc(sizeof(IntStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the character stack is empty
int isCharStackEmpty(CharStack* stack) {
    return stack->top == -1;
}

// Function to check if the integer stack is empty
int isIntStackEmpty(IntStack* stack) {
    return stack->top == -1;
}

// Function to push an item to the character stack
void pushChar(CharStack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to push an item to the integer stack
void pushInt(IntStack* stack, int item) {
    stack->array[++stack->top] = item;
}

// Function to pop an item from the character stack
char popChar(CharStack* stack) {
    if (!isCharStackEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

// Function to pop an item from the integer stack
int popInt(IntStack* stack) {
    if (!isIntStackEmpty(stack))
        return stack->array[stack->top--];
    return -1;
}

// Function to get the top item of the character stack
char peekChar(CharStack* stack) {
    if (!isCharStackEmpty(stack))
        return stack->array[stack->top];
    return '$';
}

// Function to check if a given character is an operand
int isOperand(char ch) {
    return isdigit(ch);
}

// Function to return precedence of a given operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* exp, char* postfix) {
    int i, k = 0;
    CharStack* stack = createCharStack(strlen(exp));
    if (!stack) {
        printf("Memory error\n");
        return;
    }

    for (i = 0; exp[i]; ++i) {
        // If the character is an operand, add it to output
        if (isOperand(exp[i]))
            postfix[k++] = exp[i];

        // If the character is '(', push it to stack
        else if (exp[i] == '(')
            pushChar(stack, exp[i]);

        // If the character is ')', pop and output from the stack
        // until an '(' is encountered
        else if (exp[i] == ')') {
            while (!isCharStackEmpty(stack) && peekChar(stack) != '(')
                postfix[k++] = popChar(stack);
            if (!isCharStackEmpty(stack) && peekChar(stack) != '(')
                return; // invalid expression
            else
                popChar(stack);
        } else { // an operator is encountered
            while (!isCharStackEmpty(stack) && precedence(exp[i]) <= precedence(peekChar(stack)))
                postfix[k++] = popChar(stack);
            pushChar(stack, exp[i]);
        }
    }

    // pop all the operators from the stack
    while (!isCharStackEmpty(stack))
        postfix[k++] = popChar(stack);

    postfix[k] = '\0';
}

// Function to evaluate postfix expression
int evaluatePostfix(char* exp) {
    IntStack* stack = createIntStack(strlen(exp));
    if (!stack) {
        printf("Memory error\n");
        return -1;
    }

    for (int i = 0; exp[i]; ++i) {
        // If the character is an operand, push it to the stack
        if (isOperand(exp[i]))
            pushInt(stack, exp[i] - '0');

        // If the character is an operator, pop two elements from the stack,
        // apply the operator and push the result back to the stack
        else {
            int val1 = popInt(stack);
            int val2 = popInt(stack);
            switch (exp[i]) {
                case '+': pushInt(stack, val2 + val1); break;
                case '-': pushInt(stack, val2 - val1); break;
                case '*': pushInt(stack, val2 * val1); break;
                case '/': pushInt(stack, val2 / val1); break;
            }
        }
    }
    return popInt(stack);
}

// Main function
int main() {
    char infix[100];
    char postfix[100];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);
    printf("Postfix evaluation: %d\n", evaluatePostfix(postfix));

    return 0;
}




//23.	WAP to implement stack using a singly linked list and perform following operations on it. A. PUSH, B. POP, C. StackeEmpty D. Display Stack.
#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the stack structure
typedef struct Stack {
    Node* top;
} Stack;

// Function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to initialize the stack
void initializeStack(Stack* stack) {
    stack->top = NULL;
}

// Function to check if the stack is empty
int isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(Stack* stack, int data) {
    Node* node = newNode(data);
    node->next = stack->top;
    stack->top = node;
    printf("%d pushed to stack\n", data);
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    Node* temp = stack->top;
    stack->top = stack->top->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// Function to display the stack
void displayStack(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    Node* temp = stack->top;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    Stack stack;
    initializeStack(&stack);

    int choice, value;

    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Check if Stack is Empty\n");
        printf("4. Display Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
            case 2:
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            case 3:
                if (isStackEmpty(&stack)) {
                    printf("Stack is empty\n");
                } else {
                    printf("Stack is not empty\n");
                }
                break;
            case 4:
                displayStack(&stack);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}




//24.	WAP to implement following by using stack. A. Factorial of a given number B. Generation of Fibonacci series.
#include <stdio.h>
#include <stdlib.h>

// Define the maximum size of the stack
#define MAX 100

// Stack structure definition
typedef struct {
    int data[MAX];
    int top;
} Stack;

// Stack operations
void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// Function to calculate factorial using stack
int factorial(int n) {
    Stack stack;
    initStack(&stack);
    
    for (int i = n; i > 1; i--) {
        push(&stack, i);
    }
    
    int result = 1;
    while (!isEmpty(&stack)) {
        result *= pop(&stack);
    }
    
    return result;
}

// Function to generate Fibonacci series using stack
void fibonacci(int n) {
    Stack stack;
    initStack(&stack);

    int fib[n];
    fib[0] = 0;
    fib[1] = 1;
    
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    for (int i = 0; i < n; i++) {
        push(&stack, fib[i]);
    }
    
    printf("Fibonacci series: ");
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
}

int main() {
    int number;

    // Factorial Calculation
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &number);
    printf("Factorial of %d is %d\n", number, factorial(number));

    // Fibonacci Series Generation
    printf("Enter the number of terms for Fibonacci series: ");
    scanf("%d", &number);
    fibonacci(number);

    return 0;
}






//25.	WAP to implement a linear queue using a singly linked list and perform following operations on it. A. enqueue, B. dequeue, C. QueueEmpty, D. Display queue, E. Display Front element, F. Display Rear element
#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to create an empty queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// Function to add an element to the queue
void enqueue(Queue* q, int data) {
    Node* temp = newNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove an element from the queue
int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return data;
}

// Function to display all elements in the queue
void displayQueue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to display the front element of the queue
void displayFront(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Front element is %d\n", q->front->data);
    }
}

// Function to display the rear element of the queue
void displayRear(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Rear element is %d\n", q->rear->data);
    }
}

int main() {
    Queue* q = createQueue();
    int choice, data;

    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. QueueEmpty\n4. Display Queue\n5. Display Front element\n6. Display Rear element\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the data to enqueue: ");
                scanf("%d", &data);
                enqueue(q, data);
                break;
            case 2:
                data = dequeue(q);
                if (data != -1) {
                    printf("Dequeued element is %d\n", data);
                }
                break;
            case 3:
                if (isQueueEmpty(q)) {
                    printf("Queue is empty\n");
                } else {
                    printf("Queue is not empty\n");
                }
                break;
            case 4:
                displayQueue(q);
                break;
            case 5:
                displayFront(q);
                break;
            case 6:
                displayRear(q);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}





//Write a Program to implement circular queue where user can add and remove the elements from rear and front end of the queue
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Circular queue structure
typedef struct {
    int data[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

// Function to initialize the circular queue
void initQueue(CircularQueue* q) {
    q->front = q->rear = -1;
    q->size = 0;
}

// Function to check if the queue is empty
int isQueueEmpty(CircularQueue* q) {
    return q->size == 0;
}

// Function to check if the queue is full
int isQueueFull(CircularQueue* q) {
    return q->size == MAX;
}

// Function to add an element to the rear of the queue
void enqueueRear(CircularQueue* q, int data) {
    if (isQueueFull(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (q->rear == -1) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->data[q->rear] = data;
    q->size++;
}

// Function to remove an element from the front of the queue
int dequeueFront(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    q->size--;
    return data;
}

// Function to add an element to the front of the queue
void enqueueFront(CircularQueue* q, int data) {
    if (isQueueFull(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (q->front == -1) {
        q->front = q->rear = 0;
    } else {
        q->front = (q->front - 1 + MAX) % MAX;
    }
    q->data[q->front] = data;
    q->size++;
}

// Function to remove an element from the rear of the queue
int dequeueRear(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->data[q->rear];
    if (q->rear == q->front) {
        q->rear = q->front = -1;
    } else {
        q->rear = (q->rear - 1 + MAX) % MAX;
    }
    q->size--;
    return data;
}

// Function to display all elements in the queue
void displayQueue(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int i = q->front;
    printf("Queue elements: ");
    while (1) {
        printf("%d ", q->data[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Function to display the front element of the queue
void displayFront(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Front element is %d\n", q->data[q->front]);
    }
}

// Function to display the rear element of the queue
void displayRear(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Rear element is %d\n", q->data[q->rear]);
    }
}

int main() {
    CircularQueue q;
    initQueue(&q);
    int choice, data;

    while (1) {
        printf("\n1. Enqueue at Rear\n2. Dequeue from Front\n3. Enqueue at Front\n4. Dequeue from Rear\n5. QueueEmpty\n6. Display Queue\n7. Display Front element\n8. Display Rear element\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the data to enqueue at rear: ");
                scanf("%d", &data);
                enqueueRear(&q, data);
                break;
            case 2:
                data = dequeueFront(&q);
                if (data != -1) {
                    printf("Dequeued element from front is %d\n", data);
                }
                break;
            case 3:
                printf("Enter the data to enqueue at front: ");
                scanf("%d", &data);
                enqueueFront(&q, data);
                break;
            case 4:
                data = dequeueRear(&q);
                if (data != -1) {
                    printf("Dequeued element from rear is %d\n", data);
                }
                break;
            case 5:
                if (isQueueEmpty(&q)) {
                    printf("Queue is empty\n");
                } else {
                    printf("Queue is not empty\n");
                }
                break;
            case 6:
                displayQueue(&q);
                break;
            case 7:
                displayFront(&q);
                break;
            case 8:
                displayRear(&q);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}




//WAP to perform addition of two polynomials using singly linked list.
#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into the polynomial in sorted order of exponents
void insertNode(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL && temp->next->exp >= exp) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to create a polynomial by taking user input
Node* createPolynomial() {
    Node* poly = NULL;
    int n, coeff, exp;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertNode(&poly, coeff, exp);
    }

    return poly;
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;
    Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            insertNode(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            insertNode(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            int sumCoeff = p1->coeff + p2->coeff;
            if (sumCoeff != 0) {
                insertNode(&result, sumCoeff, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        insertNode(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertNode(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Function to display a polynomial
void displayPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    
    Node* temp = poly;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != poly) {
            printf("+ ");
        }
        printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* sum = NULL;

    printf("Enter the first polynomial:\n");
    poly1 = createPolynomial();
    
    printf("Enter the second polynomial:\n");
    poly2 = createPolynomial();

    sum = addPolynomials(poly1, poly2);

    printf("First Polynomial: ");
    displayPolynomial(poly1);

    printf("Second Polynomial: ");
    displayPolynomial(poly2);

    printf("Sum of Polynomials: ");
    displayPolynomial(sum);

    return 0;
}






//Write a Reverse() function that reverses a Singly linked list and display the list
#include <stdio.h>
#include <stdlib.h>

// Node structure for the singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to reverse the singly linked list
void Reverse(struct Node** head_ref) {
    struct Node* prev = NULL;
    struct Node* current = *head_ref;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;  // Store next node
        current->next = prev;  // Reverse current node's pointer
        prev = current;        // Move pointers one position ahead
        current = next;
    }
    *head_ref = prev;  // Update head to new first node
}

// Function to push a new node to the beginning of the list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Function to print the singly linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    // Start with the empty list
    struct Node* head = NULL;

    // Add elements to the list
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);

    printf("Original Linked List:\n");
    printList(head);

    // Reverse the linked list
    Reverse(&head);

    printf("Reversed Linked List:\n");
    printList(head);

    return 0;
}





//WAP to create doubly linked list and perform following operations on it. A) Insert (all cases) 2. Delete (all cases).
#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* getNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning
void insertAtBeginning(struct Node** head_ref, int data) {
    struct Node* newNode = getNode(data);
    if (*head_ref != NULL) {
        newNode->next = *head_ref;
        (*head_ref)->prev = newNode;
    }
    *head_ref = newNode;
}

// Function to insert a node at the end
void insertAtEnd(struct Node** head_ref, int data) {
    struct Node* newNode = getNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to insert a node after a given node
void insertAfter(struct Node* prev_node, int data) {
    if (prev_node == NULL) {
        printf("The given previous node cannot be NULL\n");
        return;
    }
    struct Node* newNode = getNode(data);
    newNode->next = prev_node->next;
    newNode->prev = prev_node;
    if (prev_node->next != NULL) {
        prev_node->next->prev = newNode;
    }
    prev_node->next = newNode;
}

// Function to delete a node from the beginning
void deleteFromBeginning(struct Node** head_ref) {
    if (*head_ref == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = *head_ref;
    *head_ref = temp->next;
    if (*head_ref != NULL) {
        (*head_ref)->prev = NULL;
    }
    free(temp);
}

// Function to delete a node from the end
void deleteFromEnd(struct Node** head_ref) {
    if (*head_ref == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        *head_ref = NULL;
    }
    free(temp);
}

// Function to delete a given node
void deleteNode(struct Node** head_ref, struct Node* del_node) {
    if (*head_ref == NULL || del_node == NULL) {
        printf("Node to be deleted is NULL or list is empty.\n");
        return;
    }
    if (*head_ref == del_node) {
        *head_ref = del_node->next;
    }
    if (del_node->next != NULL) {
        del_node->next->prev = del_node->prev;
    }
    if (del_node->prev != NULL) {
        del_node->prev->next = del_node->next;
    }
    free(del_node);
}

// Function to print the doubly linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    // Insert nodes at the beginning
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);
    printf("List after inserting at the beginning:\n");
    printList(head);

    // Insert nodes at the end
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);
    printf("List after inserting at the end:\n");
    printList(head);

    // Insert node after a given node
    insertAfter(head->next, 25);  // Insert after the second node (20)
    printf("List after inserting 25 after the second node:\n");
    printList(head);

    // Delete node from the beginning
    deleteFromBeginning(&head);
    printf("List after deleting from the beginning:\n");
    printList(head);

    // Delete node from the end
    deleteFromEnd(&head);
    printf("List after deleting from the end:\n");
    printList(head);

    // Delete a specific node (e.g., node with data 25)
    deleteNode(&head, head->next->next);  // Delete the node with data 25
    printf("List after deleting a specific node (node with data 25):\n");
    printList(head);

    return 0;
}



//WAP to merge two sorted Doubly linked lists and display their result.
#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* getNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end
void insertAtEnd(struct Node** head_ref, int data) {
    struct Node* newNode = getNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to merge two sorted doubly linked lists
struct Node* mergeSortedLists(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    if (head1->data < head2->data) {
        head1->next = mergeSortedLists(head1->next, head2);
        head1->next->prev = head1;
        head1->prev = NULL;
        return head1;
    } else {
        head2->next = mergeSortedLists(head1, head2->next);
        head2->next->prev = head2;
        head2->prev = NULL;
        return head2;
    }
}

// Function to print the doubly linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    // Create first sorted doubly linked list: 1 <-> 3 <-> 5 <-> 7
    insertAtEnd(&head1, 1);
    insertAtEnd(&head1, 3);
    insertAtEnd(&head1, 5);
    insertAtEnd(&head1, 7);

    // Create second sorted doubly linked list: 2 <-> 4 <-> 6 <-> 8
    insertAtEnd(&head2, 2);
    insertAtEnd(&head2, 4);
    insertAtEnd(&head2, 6);
    insertAtEnd(&head2, 8);

    printf("First Sorted Doubly Linked List:\n");
    printList(head1);

    printf("Second Sorted Doubly Linked List:\n");
    printList(head2);

    // Merge the two sorted doubly linked lists
    struct Node* mergedHead = mergeSortedLists(head1, head2);

    printf("Merged Sorted Doubly Linked List:\n");
    printList(mergedHead);

    return 0;
}



//31.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Postorder way.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left, *right;
    int data;
    int rightThread;
} Node;

Node *createNode(int item) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->data = item;
    node->rightThread = 0;
    return node;
}

void createThreaded(Node *root) {
    static Node *prev = NULL;
    if (root == NULL)
        return;
    createThreaded(root->left);
    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->rightThread = 1;
    }
    if (root->left == NULL)
        root->left = prev;
    prev = root;
    createThreaded(root->right);
}

// Function to find the rightmost node in a subtree
Node* rightmost(Node* node) {
    while (node != NULL && node->rightThread == 0 && node->right != NULL)
        node = node->right;
    return node;
}

// Function to find the postorder predecessor of a node
Node* postorderPredecessor(Node* node) {
    // If the node has a left child, the predecessor is the rightmost node of the left child
    if (node->left != NULL && node->left->right != node) {
        return rightmost(node->left);
    }
    // Otherwise, return the left child itself
    return node->left;
}

// Function to perform postorder traversal of the threaded binary tree
void postOrderTraversal(Node* root) {
    Node* curr = rightmost(root);
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = postorderPredecessor(curr);
    }
}

int main() {
    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    createThreaded(root);

    printf("Postorder traversal of the created threaded binary tree is: \n");
    postOrderTraversal(root);

    return 0;
}
