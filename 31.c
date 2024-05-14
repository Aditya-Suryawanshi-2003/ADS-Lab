#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left, *right;
    int data;
    int rightThread;
} Node;

Node *createNode(int item) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->data = item;
    node->rightThread = 0;
    return node;
}

void createThreaded(Node *root) {
    static Node *prev = NULL;
    if (root == NULL)
        return;
    createThreaded(root->left);
    if (prev != NULL && prev->right == NULL) {
        prev->right = root;
        prev->rightThread = 1;
    }
    if (root->left == NULL)
        root->left = prev;
    prev = root;
    createThreaded(root->right);
}

// Function to find the rightmost node in a subtree
Node* rightmost(Node* node) {
    while (node != NULL && node->rightThread == 0 && node->right != NULL)
        node = node->right;
    return node;
}

// Function to find the postorder predecessor of a node
Node* postorderPredecessor(Node* node) {
    // If the node has a left child, the predecessor is the rightmost node of the left child
    if (node->left != NULL && node->left->right != node) {
        return rightmost(node->left);
    }
    // Otherwise, return the left child itself
    return node->left;
}

// Function to perform postorder traversal of the threaded binary tree
void postOrderTraversal(Node* root) {
    Node* curr = rightmost(root);
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = postorderPredecessor(curr);
    }
}

int main() {
    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    createThreaded(root);

    printf("Postorder traversal of the created threaded binary tree is: \n");
    postOrderTraversal(root);

    return 0;
}
