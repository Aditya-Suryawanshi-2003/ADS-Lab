
//11.	Write a program to efficiently search a particular employee record by using Tree data structure. Also sort the data on emp-id in ascending order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an employee
typedef struct Employee {
    int emp_id;
    char name[100];
    struct Employee *left, *right;
} Employee;

// Function to create a new employee node
Employee* createEmployee(int emp_id, char* name) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert a new employee into the BST
Employee* insertEmployee(Employee* root, int emp_id, char* name) {
    if (root == NULL) return createEmployee(emp_id, name);
    
    if (emp_id < root->emp_id)
        root->left = insertEmployee(root->left, emp_id, name);
    else if (emp_id > root->emp_id)
        root->right = insertEmployee(root->right, emp_id, name);
    
    return root;
}

// Function to search for an employee by emp_id
Employee* searchEmployee(Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) return root;
    
    if (emp_id < root->emp_id)
        return searchEmployee(root->left, emp_id);
    else
        return searchEmployee(root->right, emp_id);
}

// In-order traversal to print employees in ascending order of emp_id
void inOrderTraversal(Employee* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Employee ID: %d, Name: %s\n", root->emp_id, root->name);
        inOrderTraversal(root->right);
    }
}

// Main function
int main() {
    Employee* root = NULL;
    root = insertEmployee(root, 102, "Alice");
    root = insertEmployee(root, 101, "Bob");
    root = insertEmployee(root, 104, "Charlie");
    root = insertEmployee(root, 103, "David");
    
    printf("Employees in ascending order of emp_id:\n");
    inOrderTraversal(root);

    int emp_id_to_search = 103;
    Employee* searchedEmployee = searchEmployee(root, emp_id_to_search);
    if (searchedEmployee != NULL) {
        printf("Employee found: ID: %d, Name: %s\n", searchedEmployee->emp_id, searchedEmployee->name);
    } else {
        printf("Employee with ID %d not found.\n", emp_id_to_search);
    }

    return 0;
}
