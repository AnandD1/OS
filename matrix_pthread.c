#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 4 // Defining the size of matrices (for simplicity)

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

// Structure to hold parameters for each thread
typedef struct {
    int row; // Row number of the result matrix
    int col; // Column number of the result matrix
} MatrixPos;

// Function for each thread to compute a single element of the result matrix
void* multiply_element(void* arg) {
    MatrixPos* pos = (MatrixPos*)arg;
    int sum = 0;
    for (int i = 0; i < MAX; i++) {
        sum += A[pos->row][i] * B[i][pos->col];
    }
    C[pos->row][pos->col] = sum;
    free(pos); // Free the memory allocated for this thread's argument
    pthread_exit(0); // Exit the thread
}

int main() {
    pthread_t threads[MAX][MAX]; // Array of thread identifiers

    // Initialize matrices A and B with example values
    printf("Matrix A:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10; // Random values between 0 and 9
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            B[i][j] = rand() % 10; // Random values between 0 and 9
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Create a thread for each element of the result matrix
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            MatrixPos* pos = (MatrixPos*)malloc(sizeof(MatrixPos)); // Allocate memory for thread argument
            pos->row = i;
            pos->col = j;
            pthread_create(&threads[i][j], NULL, multiply_element, pos); // Create the thread
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            pthread_join(threads[i][j], NULL); // Wait for the thread to finish
        }
    }

    // Print the result matrix
    printf("Matrix C (Result):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
