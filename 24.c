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
