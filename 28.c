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
