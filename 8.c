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


