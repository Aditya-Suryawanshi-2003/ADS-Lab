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
