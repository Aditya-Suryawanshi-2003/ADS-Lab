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
