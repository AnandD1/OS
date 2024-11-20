#include <stdio.h>

// Structure to represent a process
typedef struct {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
} Process;

// Function to sort processes by priority
void sortProcessesByPriority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                // Swap processes
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void calculateTimes(Process processes[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival; // CPU waits if no process arrives
        }
        processes[i].waiting = currentTime - processes[i].arrival;
        currentTime += processes[i].burst;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
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
    }

    // Sort by priority
    sortProcessesByPriority(processes, n);

    // Calculate times
    calculateTimes(processes, n);

    // Display results
    displayResults(processes, n);

    return 0;
}
