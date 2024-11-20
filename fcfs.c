#include <stdio.h>

void calculate_waiting_time(int processes[], int n, int burst_time[], int waiting_time[]) {
    waiting_time[0] = 0;  // Waiting time for the first process is always 0

    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
    }
}

void calculate_turnaround_time(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

void calculate_finish_time(int turnaround_time[], int arrival_time[], int finish_time[], int n) {
    for (int i = 0; i < n; i++) {
        finish_time[i] = turnaround_time[i] + arrival_time[i];
    }
}

void find_times(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n], finish_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate times
    calculate_waiting_time(processes, n, burst_time, waiting_time);
    calculate_turnaround_time(processes, n, burst_time, waiting_time, turnaround_time);
    calculate_finish_time(turnaround_time, arrival_time, finish_time, n);

    // Display results
    printf("Process\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], finish_time[i], turnaround_time[i], waiting_time[i]);
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

    // Initialize process IDs
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
    find_times(processes, n, burst_time, arrival_time);

    return 0;
}
