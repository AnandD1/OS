#include <stdio.h>

void calculate_waiting_time(int n, int processes[], int burst_time[], int waiting_time[], int arrival_time[]) {
    int completion_time[n];
    int is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;  // Mark all processes as incomplete initially
    }

    int current_time = 0, completed = 0;

    while (completed < n) {
        int shortest = -1;  // Index of the shortest job
        int min_burst_time = 1e9;

        // Find the shortest job that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && !is_completed[i]) {
                if (burst_time[i] < min_burst_time || 
                   (burst_time[i] == min_burst_time && arrival_time[i] < arrival_time[shortest])) {
                    min_burst_time = burst_time[i];
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            current_time++;  // No process is ready, increment time
            continue;
        }

        // Update completion time and waiting time
        completion_time[shortest] = current_time + burst_time[shortest];
        waiting_time[shortest] = current_time - arrival_time[shortest];
        current_time = completion_time[shortest];
        is_completed[shortest] = 1;  // Mark the process as completed
        completed++;
    }
}

void calculate_turnaround_time(int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

void find_avg_times(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate waiting and turnaround times
    calculate_waiting_time(n, processes, burst_time, waiting_time, arrival_time);
    calculate_turnaround_time(n, burst_time, waiting_time, turnaround_time);

    // Display results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    // Input processes IDs
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
    }

    // Input burst times
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Input arrival times
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }

    // Calculate and display times
    find_avg_times(processes, n, burst_time, arrival_time);

    return 0;
}
