#include <stdio.h>
void fcfs (int num_processes, int arrival_time[], int burst_time[]) {
    int completion_time[num_processes];
    int waiting_time[num_processes];
    int response_time[num_processes];
    int turnaround_time[num_processes];

    completion_time[0] = arrival_time[0];

    for (int i = 1; i < num_processes; i++) {
       
        completion_time[i] = burst_time[i] + completion_time[i-1];

        waiting_time[i] = completion_time[i] - arrival_time[i];

        response_time[i] = waiting_time[i];

        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
    float avg_waiting_time = 0.0;
    float avg_response_time = 0.0;
    float avg_turnaround_time = 0.0;

    for (int i = 0; i < num_processes; i++) {
        avg_waiting_time += waiting_time[i];
        avg_response_time += response_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    avg_waiting_time /= num_processes;
    avg_response_time /= num_processes;
    avg_turnaround_time /= num_processes;

    printf("Order of process execution: ");

    for (int i = 0; i < num_processes; i++) {
        printf("%d ", i + 1);
    }

    printf("\n");
    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average response time: %.2f\n", avg_response_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

int main() {
    int num_processes;
    int arrival_time[10];
    int burst_time[10];
    int scheduling_type;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the arrival time for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter the CPU burst time for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        scanf("%d", &burst_time[i]);
    }

    printf("Enter the scheduling type (0 for non-preemptive, 1 for preemptive): ");
    scanf("%d", &scheduling_type);

    if (scheduling_type == 0) {
        fcfs(num_processes, arrival_time, burst_time);
    }
    else {
        printf("Preemptive FCFS not implemented.\n");
    }

    return 0;
}
