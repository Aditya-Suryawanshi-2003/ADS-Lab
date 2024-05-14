#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Circular queue structure
typedef struct {
    int data[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

// Function to initialize the circular queue
void initQueue(CircularQueue* q) {
    q->front = q->rear = -1;
    q->size = 0;
}

// Function to check if the queue is empty
int isQueueEmpty(CircularQueue* q) {
    return q->size == 0;
}

// Function to check if the queue is full
int isQueueFull(CircularQueue* q) {
    return q->size == MAX;
}

// Function to add an element to the rear of the queue
void enqueueRear(CircularQueue* q, int data) {
    if (isQueueFull(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (q->rear == -1) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->data[q->rear] = data;
    q->size++;
}

// Function to remove an element from the front of the queue
int dequeueFront(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    q->size--;
    return data;
}

// Function to add an element to the front of the queue
void enqueueFront(CircularQueue* q, int data) {
    if (isQueueFull(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (q->front == -1) {
        q->front = q->rear = 0;
    } else {
        q->front = (q->front - 1 + MAX) % MAX;
    }
    q->data[q->front] = data;
    q->size++;
}

// Function to remove an element from the rear of the queue
int dequeueRear(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->data[q->rear];
    if (q->rear == q->front) {
        q->rear = q->front = -1;
    } else {
        q->rear = (q->rear - 1 + MAX) % MAX;
    }
    q->size--;
    return data;
}

// Function to display all elements in the queue
void displayQueue(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int i = q->front;
    printf("Queue elements: ");
    while (1) {
        printf("%d ", q->data[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Function to display the front element of the queue
void displayFront(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Front element is %d\n", q->data[q->front]);
    }
}

// Function to display the rear element of the queue
void displayRear(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Rear element is %d\n", q->data[q->rear]);
    }
}

int main() {
    CircularQueue q;
    initQueue(&q);
    int choice, data;

    while (1) {
        printf("\n1. Enqueue at Rear\n2. Dequeue from Front\n3. Enqueue at Front\n4. Dequeue from Rear\n5. QueueEmpty\n6. Display Queue\n7. Display Front element\n8. Display Rear element\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the data to enqueue at rear: ");
                scanf("%d", &data);
                enqueueRear(&q, data);
                break;
            case 2:
                data = dequeueFront(&q);
                if (data != -1) {
                    printf("Dequeued element from front is %d\n", data);
                }
                break;
            case 3:
                printf("Enter the data to enqueue at front: ");
                scanf("%d", &data);
                enqueueFront(&q, data);
                break;
            case 4:
                data = dequeueRear(&q);
                if (data != -1) {
                    printf("Dequeued element from rear is %d\n", data);
                }
                break;
            case 5:
                if (isQueueEmpty(&q)) {
                    printf("Queue is empty\n");
                } else {
                    printf("Queue is not empty\n");
                }
                break;
            case 6:
                displayQueue(&q);
                break;
            case 7:
                displayFront(&q);
                break;
            case 8:
                displayRear(&q);
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
