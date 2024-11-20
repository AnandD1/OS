#include <stdio.h>
#include <limits.h> // For INT_MAX

void find_waiting_time(int n, int processes[], int burst_time[], int arrival_time[], int waiting_time[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i]; // Initialize remaining time for all processes
    }

    int completed = 0, current_time = 0, shortest = -1, finish_time;
    int min_remaining_time = INT_MAX;
    int is_process_found = 0;

    while (completed != n) {
        // Find process with the smallest remaining time and that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] < min_remaining_time && remaining_time[i] > 0) {
                min_remaining_time = remaining_time[i];
                shortest = i;
                is_process_found = 1;
            }
        }

        if (!is_process_found) {
            current_time++; // Increment time if no process is ready
            continue;
        }

        // Reduce remaining time for the selected process
        remaining_time[shortest]--;
        min_remaining_time = remaining_time[shortest];

        // If a process finishes, update completion details
        if (remaining_time[shortest] == 0) {
            completed++;
            is_process_found = 0;
            min_remaining_time = INT_MAX;

            finish_time = current_time + 1;
            waiting_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];

            if (waiting_time[shortest] < 0) {
                waiting_time[shortest] = 0; // Waiting time cannot be negative
            }
        }
        current_time++;
    }
}

void find_turnaround_time(int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

void find_avg_times(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate waiting time and turnaround time
    find_waiting_time(n, processes, burst_time, arrival_time, waiting_time);
    find_turnaround_time(n, burst_time, waiting_time, turnaround_time);

    // Print the results
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
