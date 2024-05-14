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
