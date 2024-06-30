#include <stdio.h>

struct process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void waitingtime(struct process p[], int n) {
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }
}

void turnaroundtime(struct process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void line(int x) {
    for (int i = 0; i < x; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    int num;
    printf("Enter the total number of Processes: ");
    scanf("%d", &num);
    
    struct process p[num];  // Use variable-length array if supported by the compiler

    for (int i = 0; i < num; i++) {
        printf("Enter the Burst time for Process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
    }

    waitingtime(p, num);
    turnaroundtime(p, num);

    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    for (int i = 0; i < num; i++) {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    line(44);
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    line(44);
    for (int i = 0; i < num; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
    line(44);

    printf("Average Waiting Time: %.2f\n", total_waiting_time / num);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / num);

    return 0;
}
