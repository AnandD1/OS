#include <stdio.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority
    int remaining;  // Remaining burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completed;  // Completion flag
} Process;

// Function to find the process with the highest priority (lowest number)
int findHighestPriorityProcess(Process processes[], int n, int currentTime) {
    int minPriority = INT_MAX;
    int processIndex = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival <= currentTime && 
            processes[i].remaining > 0 && 
            processes[i].priority < minPriority) {
            minPriority = processes[i].priority;
            processIndex = i;
        }
    }
    return processIndex;
}

// Function to calculate waiting and turnaround times
void calculateTimes(Process processes[], int n) {
    int currentTime = 0, completedProcesses = 0;

    while (completedProcesses < n) {
        // Find the highest-priority process that is ready
        int currentProcess = findHighestPriorityProcess(processes, n, currentTime);

        if (currentProcess != -1) {
            // Execute the process for 1 unit of time
            processes[currentProcess].remaining--;
            currentTime++;

            // If the process is completed
            if (processes[currentProcess].remaining == 0) {
                completedProcesses++;
                int completionTime = currentTime;
                processes[currentProcess].turnaround = completionTime - processes[currentProcess].arrival;
                processes[currentProcess].waiting = processes[currentProcess].turnaround - processes[currentProcess].burst;
            }
        } else {
            // No process is ready, increment time
            currentTime++;
        }
    }
}

// Function to display the results
void displayResults(Process processes[], int n) {
    printf("ID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    int totalWaiting = 0, totalTurnaround = 0;

    for (int i = 0; i < n; i++) {
        totalWaiting += processes[i].waiting;
        totalTurnaround += processes[i].turnaround;
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].priority, processes[i].waiting, processes[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
        processes[i].remaining = processes[i].burst;
        processes[i].completed = 0;
    }

    // Calculate times
    calculateTimes(processes, n);

    // Display results
    displayResults(processes, n);

    return 0;
}
