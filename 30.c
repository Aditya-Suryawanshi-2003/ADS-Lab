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
