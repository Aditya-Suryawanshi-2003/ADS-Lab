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
