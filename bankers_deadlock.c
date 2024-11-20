#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeedMatrix(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int alloc[MAX_PROCESSES][MAX_RESOURCES], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafeState(int processes[], int avail[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int n, int m) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeedMatrix(need, max, alloc, n, m);

    bool finished[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    // Initialize work array to available resources
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0; // Count of processes safely executed

    while (count < n) {
        bool foundProcess = false;

        for (int p = 0; p < n; p++) {
            if (!finished[p]) { // If process is not finished
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break; // Process cannot be allocated
                    }
                }

                if (j == m) { // If all resources can be allocated
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[p][k]; // Release allocated resources
                    }

                    safeSequence[count++] = p;
                    finished[p] = true;
                    foundProcess = true;
                }
            }
        }

        if (!foundProcess) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int processes[MAX_PROCESSES];
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    isSafeState(processes, avail, max, alloc, n, m);

    return 0;
}
