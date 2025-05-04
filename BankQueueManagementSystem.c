#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // for sleep() - provide access to operating system API

#define MAX_TELLERS 5
#define MAX_CUSTOMERS 100

struct Customer {
    int id;
    int serviceTime;
    int remainingTime;
    int waitingTime;
    time_t arrivalTime;
    time_t startTime;
    time_t endTime;
};

struct Teller {
    int id;
    int servedCount;
    struct Customer* queue[MAX_CUSTOMERS];
    int front, rear;
    struct Customer* served[MAX_CUSTOMERS];
    int servedIndex;
    int totalServiceTime;
    int totalBusyTime;
};
Teller tellers[MAX_TELLERS];

int customerIdCounter = 1;

double totalWaitingTime = 0;
double totalServiceTime = 0;
int totalCustomersServed = 0;

time_t globalClock;

void initTellers() {
    for (int i = 0; i < MAX_TELLERS; i++) {
        tellers[i].id = i + 1;
        tellers[i].servedCount = 0;
        tellers[i].front = 0;
        tellers[i].rear = 0;
        tellers[i].servedIndex = 0;
        tellers[i].totalServiceTime = 0;
        tellers[i].totalBusyTime = 0;
    }
}

int getTellerWithLeastCustomers() {
    int minIndex = 0;
    int minQueueSize = tellers[0].rear - tellers[0].front;
    for (int i = 1; i < MAX_TELLERS; i++) {
        int currentSize = tellers[i].rear - tellers[i].front;
        if (currentSize < minQueueSize) {
            minQueueSize = currentSize;
            minIndex = i;
        }
    }
    return minIndex;
}

void enqueueCustomer() {
    struct Customer* newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
    newCustomer->id = customerIdCounter++;
    newCustomer->serviceTime = (rand() % 5) + 5; // service time 
    newCustomer->remainingTime = newCustomer->serviceTime;
    newCustomer->arrivalTime = time(NULL);

    int tellerIndex = getTellerWithLeastCustomers();
    tellers[tellerIndex].queue[tellers[tellerIndex].rear++] = newCustomer;

    printf("\nCustomer %d assigned to Teller %d with service time %d seconds.\n",
           newCustomer->id, tellers[tellerIndex].id, newCustomer->serviceTime);
}

void processCustomers() {
    for (int i = 0; i < MAX_TELLERS; i++) {
        if (tellers[i].front < tellers[i].rear) {
            struct Customer* current = tellers[i].queue[tellers[i].front];
            if (current->remainingTime == current->serviceTime) {
                current->startTime = time(NULL);
                current->waitingTime = difftime(current->startTime, current->arrivalTime);
                totalWaitingTime += current->waitingTime;
                tellers[i].totalBusyTime += current->serviceTime;
            }
            current->remainingTime--;
            if (current->remainingTime <= 0) {
                current->endTime = time(NULL);
                totalServiceTime += current->serviceTime;
                totalCustomersServed++;

                tellers[i].served[tellers[i].servedIndex++] = current;
                tellers[i].servedCount++;
                tellers[i].totalServiceTime += current->serviceTime;
                tellers[i].front++;
                printf("\nCustomer %d served by Teller %d.\n", current->id, tellers[i].id);
            }
        }
    }
}

void displayCustomers() {
    printf("\n\n--------- Current Teller Queues ---------\n\n");
    for (int i = 0; i < MAX_TELLERS; i++) {
        printf("Teller %d queue: ", tellers[i].id);
        if (tellers[i].front == tellers[i].rear) {
            printf("No customers\n");
            continue;
        }
        for (int j = tellers[i].front; j < tellers[i].rear; j++) {
            printf("[C%d - %ds] ", tellers[i].queue[j]->id, tellers[i].queue[j]->remainingTime);
        }
        printf("\n");
    }
    printf("\n-----------------------------------------\n\n");
}

void displayTellerStats() {
    printf("\n\n--------- Teller Service History ---------\n\n");
    for (int i = 0; i < MAX_TELLERS; i++) {
        printf("Teller %d served %d customers:\n", tellers[i].id, tellers[i].servedCount);
        for (int j = 0; j < tellers[i].servedIndex; j++) {
            printf("  Customer %d - Service Time: %d seconds\n",
                   tellers[i].served[j]->id, tellers[i].served[j]->serviceTime);
        }
        int customersRemaining = tellers[i].rear - tellers[i].front;
        printf("  Customers Remaining in Queue: %d\n", customersRemaining);
        printf("  Teller Status: %s\n", customersRemaining == 0 ? "Available" : "Busy");
        printf("\n");
    }
    printf("------------------------------------------\n");
}

void displayAnalysis() {
    printf("\n\n--------- Waiting Time Analysis ---------\n\n");
    if (totalCustomersServed == 0) {
        printf("No customers have been served yet.\n");
    } else {
        printf("Average Waiting Time: %.2f seconds\n", totalWaitingTime / totalCustomersServed);
        printf("Average Service Time: %.2f seconds\n\n", totalServiceTime / totalCustomersServed);
    }
    for (int i = 0; i < MAX_TELLERS; i++) {
        int totalElapsed = time(NULL) - globalClock;
        double utilization = (double)tellers[i].totalBusyTime / totalElapsed * 100;
        printf("Teller %d Utilization: %.2f%%\n", tellers[i].id, utilization);
    }
    printf("\n------------------------------------------\n\n");
}

int main() {
	printf("\n--- ~~ --- ~~ BANK QUEUE MANAGEMENT SYSTEM ~~ --- ~~ ---\n\n");
    int choice;
    srand(time(NULL));
    initTellers();
    globalClock = time(NULL);

    while (1) {
        printf("\n1. Add Customer\n2. Display Current Customers\n3. Display Teller Stats\n4. Waiting Time Analysis\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueueCustomer();
                break;
            case 2:
                displayCustomers();
                break;
            case 3:
                displayTellerStats();
                break;
            case 4:
                displayAnalysis();
                break;
            case 0:
                printf("Thank you for using BQMS.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }

        processCustomers();
        sleep(1);
    }
    return 0;
}
