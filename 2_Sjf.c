#include <stdio.h>
void sjf(int num_processes, int arrival_time[], int burst_time[]) {
    int completion_time[num_processes];
    int waiting_time[num_processes];
    int response_time[num_processes];
    int turnaround_time[num_processes];
    int remaining_time[num_processes];

    for (int i = 0; i < num_processes; i++) {
        remaining_time[i] = burst_time[i];
    }

    int time = 0;  
    int completed = 0;  

    while (completed < num_processes) {
        int min_burst_time = 99999;
        int shortest_job_index = -1;

        for (int i = 0; i < num_processes; i++) {
            if (arrival_time[i] <= time && remaining_time[i] < min_burst_time && remaining_time[i] > 0) {
                min_burst_time = remaining_time[i];
                shortest_job_index = i;
            }
        }

        if (shortest_job_index == -1) {
            time++;
            continue;
        }

        completion_time[shortest_job_index] = time + remaining_time[shortest_job_index];

        waiting_time[shortest_job_index] = completion_time[shortest_job_index] - burst_time[shortest_job_index] - arrival_time[shortest_job_index];

        response_time[shortest_job_index] = waiting_time[shortest_job_index];

        turnaround_time[shortest_job_index] = completion_time[shortest_job_index] - arrival_time[shortest_job_index];
        completed++;
        remaining_time[shortest_job_index] = 0;

        time = completion_time[shortest_job_index];
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
    printf("Average response time: %.2
