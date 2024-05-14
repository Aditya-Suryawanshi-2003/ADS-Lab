//21.	WAP to implement Heap sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks), with key as student_roll_no. And count the number of swap performed.
#include <stdio.h>
#include <string.h>

// Define the Student structure
typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

int swap_count = 0; // Global variable to count the number of swaps

// Function to merge two halves
void merge(Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            swap_count += (n1 - i); // Increment swap count by the number of remaining elements in L[]
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(Student arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to print the array
void printArray(Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Roll No: %d, Total Marks: %d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

// Main function
int main() {
    Student arr[] = {
        {"Alice", 5, 85},
        {"Bob", 2, 75},
        {"Charlie", 8, 95},
        {"David", 1, 65},
        {"Eve", 7, 80}
    };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is:\n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is:\n");
    printArray(arr, arr_size);

    printf("\nNumber of swaps performed: %d\n", swap_count);
    return 0;
}
