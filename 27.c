#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node into the polynomial in sorted order of exponents
void insertNode(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL && temp->next->exp >= exp) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to create a polynomial by taking user input
Node* createPolynomial() {
    Node* poly = NULL;
    int n, coeff, exp;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertNode(&poly, coeff, exp);
    }

    return poly;
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;
    Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            insertNode(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            insertNode(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            int sumCoeff = p1->coeff + p2->coeff;
            if (sumCoeff != 0) {
                insertNode(&result, sumCoeff, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        insertNode(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertNode(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Function to display a polynomial
void displayPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    
    Node* temp = poly;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != poly) {
            printf("+ ");
        }
        printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* sum = NULL;

    printf("Enter the first polynomial:\n");
    poly1 = createPolynomial();
    
    printf("Enter the second polynomial:\n");
    poly2 = createPolynomial();

    sum = addPolynomials(poly1, poly2);

    printf("First Polynomial: ");
    displayPolynomial(poly1);

    printf("Second Polynomial: ");
    displayPolynomial(poly2);

    printf("Sum of Polynomials: ");
    displayPolynomial(sum);

    return 0;
}
