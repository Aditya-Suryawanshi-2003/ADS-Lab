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
