#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
} Process;

void displayReadyQueue(int queue[], int front, int rear) {
    printf("Ready Queue: ");
    if (front > rear) {
        printf("Empty\n");
        return;
    }
    for (int i = front; i <= rear; i++) {
        printf("P%d ", queue[i] + 1); // Process IDs are 1-indexed
    }
    printf("\n");
}

void roundRobin(Process processes[], int n, int quantum) {
    int currentTime = 0;
    int completed = 0;
    int queue[MAX], front = 0, rear = -1;

    // Push all processes that have arrived at time 0 into the ready queue
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival <= currentTime) {
            queue[++rear] = i; // Add process index to the ready queue
        }
    }

    while (completed < n) {
        if (front > rear) { // No process in ready queue
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                    queue[++rear] = i;
                }
            }
            continue;
        }

        int currentProcess = queue[front++]; // Dequeue process

        // Display the ready queue before execution
        displayReadyQueue(queue, front, rear);

        if (processes[currentProcess].remaining > 0) {
            int execTime = (processes[currentProcess].remaining < quantum) 
                                ? processes[currentProcess].remaining 
                                : quantum;

            // Execute the process
            processes[currentProcess].remaining -= execTime;
            currentTime += execTime;

            // Add newly arrived processes to the queue
            for (int i = 0; i < n; i++) {
                if (i != currentProcess && processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                    int isInQueue = 0;
                    for (int j = front; j <= rear; j++) {
                        if (queue[j] == i) {
                            isInQueue = 1;
                            break;
                        }
                    }
                    if (!isInQueue) {
                        queue[++rear] = i; // Enqueue new processes
                    }
                }
            }

            // If process is not complete, requeue it
            if (processes[currentProcess].remaining > 0) {
                queue[++rear] = currentProcess;
            } else { // Process is complete
                processes[currentProcess].turnaround = currentTime - processes[currentProcess].arrival;
                processes[currentProcess].waiting = processes[currentProcess].turnaround - processes[currentProcess].burst;
                completed++;
            }
        }
    }
}

void displayResults(Process processes[], int n) {
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    int totalWaiting = 0, totalTurnaround = 0;

    for (int i = 0; i < n; i++) {
        totalWaiting += processes[i].waiting;
        totalTurnaround += processes[i].turnaround;
        printf("P%d\t%d\t%d\t%d\t%d\n", 
               processes[i].id, processes[i].arrival, 
               processes[i].burst, processes[i].waiting, 
               processes[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Perform round-robin scheduling
    roundRobin(processes, n, quantum);

    // Display results
    displayResults(processes, n);

    return 0;
}
