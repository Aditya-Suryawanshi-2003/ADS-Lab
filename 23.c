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
