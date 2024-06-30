#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 5

bool canGrantRequest(int request[], int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int numProcesses, int numResources, int process) {
	
    for (int i = 0; i < numResources; i++) {
        if (request[i] > need[process][i]) {
            return false;
        }
    }

    for (int i = 0; i < numResources; i++) {
        if (request[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < numResources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < numProcesses) {
        bool found = false;
        for (int p = 0; p < numProcesses; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < numResources; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == numResources) {
                    for (int k = 0; k < numResources; k++) {
                        work[k] += allocation[p][k];
                    }

                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            for (int i = 0; i < numResources; i++) {
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }

            return false;
        }
    }

    for (int i = 0; i < numResources; i++) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }

    return true;
}

bool detectDeadlock(int allocation[][MAX_RESOURCES], int max[][MAX_RESOURCES], int available[], int numProcesses, int numResources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (int p = 0; p < numProcesses; p++) {
        int request[MAX_RESOURCES] = {0};
        for (int i = 0; i < numResources; i++) {
            request[i] = need[p][i];
        }

        if (!canGrantRequest(request, available, allocation, need, numProcesses, numResources, p)) {
            return true; 
        }
    }

    return false;
}

int main() {
    int numProcesses, numResources;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    if (detectDeadlock(allocation, max, available, numProcesses, numResources)) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}

