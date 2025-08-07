#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISPATCHERS 5
#define MAX_ORDERS 100

// Order structure
typedef struct {
    int orderID;
    int customerID;
    int food;
    int prepTime;
    int deliveryDistance;
    int priority;
    int assigned; // 0--> not assigned, 1--> assigned
} Order;

// Dispatcher structure
typedef struct {
    int dispatcherID;
    int isAvailable;
    int currentOrderID;
    int remainingTime;
} Dispatcher;

//completed structure
typedef struct {
    int orderID;
    int customerID;
    int dispatcherID;
    int totalTime;
} CompletedOrder;

CompletedOrder completedOrders[MAX_ORDERS];
int completedOrderCount = 0;

Order *orderQueue[MAX_ORDERS]; // Priority Queue
int orderCount = 0;

Dispatcher dispatchers[MAX_DISPATCHERS];
int timeTick = 0;

// Function Prototypes
void addOrder();
void insertOrderInPriorityQueue(Order *);
void assignOrders();
void simulateTime();
void viewOrders();
void viewDispatchers();

// Main Menu
int main() {
    // Initialize dispatchers
    for (int i = 0; i < MAX_DISPATCHERS; i++) {
        dispatchers[i].dispatcherID = i + 1;
        dispatchers[i].isAvailable = 1;
        dispatchers[i].currentOrderID = -1;
        dispatchers[i].remainingTime = 0;
    }

    int choice;
    while (1) {
    	simulateTime();
        printf("\n--- Food Delivery Dispatcher System ---\n");
        printf("1. Add Order\n2. Assign Orders\n3. Simulate Time\n4. View Orders\n5. View Dispatchers\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addOrder(); break;
            case 2: assignOrders(); break;
            case 3: simulateTime(); break;
            case 4: viewOrders(); break;
            case 5: viewDispatchers(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Add new order
void addOrder() {
    Order *newOrder = (Order *)malloc(sizeof(Order));
    newOrder->orderID = orderCount + 1;
    printf("Enter Customer ID: "); scanf("%d", &newOrder->customerID);
    printf("Enter FoodId: "); scanf("%d", &newOrder->food);
    printf("Enter Preparation Time (in Minutes): "); scanf("%d", &newOrder->prepTime);
    printf("Enter Delivery Distance (in KM): "); scanf("%d", &newOrder->deliveryDistance);
    printf("Enter Priority (higher number = higher priority): "); scanf("%d", &newOrder->priority);
    newOrder->assigned = 0;
    insertOrderInPriorityQueue(newOrder);
    printf("Order %d added successfully!\n", newOrder->orderID);
}

// Insert into priority queue based on priority (descending order)
void insertOrderInPriorityQueue(Order *order) {
    int i = orderCount - 1;
    while (i >= 0 && orderQueue[i]->priority < order->priority) {
        orderQueue[i + 1] = orderQueue[i];
        i--;
    }
    orderQueue[i + 1] = order;
    orderCount++;
}

// Assign highest priority orders to available dispatchers
void assignOrders() {
    for (int i = 0; i < orderCount; i++) {
        if (orderQueue[i]->assigned == 1)
            continue;
        for (int j = 0; j < MAX_DISPATCHERS; j++) {
            if (dispatchers[j].isAvailable) {
                int totalTime = orderQueue[i]->prepTime + orderQueue[i]->deliveryDistance;
                dispatchers[j].isAvailable = 0;
                dispatchers[j].currentOrderID = orderQueue[i]->orderID;
                dispatchers[j].remainingTime = totalTime;
                orderQueue[i]->assigned = 1;
                printf("Assigned Order %d to Dispatcher %d\n", orderQueue[i]->orderID, dispatchers[j].dispatcherID);
                break;
            }
        }
    }
}

// Simulate one time tick
void simulateTime() {
    timeTick++;
    //printf("\n--- Time Tick: %d ---\n", timeTick);
    for (int i = 0; i < MAX_DISPATCHERS; i++) {
        if (!dispatchers[i].isAvailable) {
            dispatchers[i].remainingTime--;
            if (dispatchers[i].remainingTime <= 0) {
               printf("\n\nDispatcher %d completed Order %d\n\n", dispatchers[i].dispatcherID, dispatchers[i].currentOrderID);
    
    // Find order details
    			for (int k = 0; k < orderCount; k++) {
        			if (orderQueue[k]->orderID == dispatchers[i].currentOrderID) {
        				orderQueue[k]->assigned = 2;
            			completedOrders[completedOrderCount].orderID = orderQueue[k]->orderID;
            			completedOrders[completedOrderCount].customerID = orderQueue[k]->customerID;
            			completedOrders[completedOrderCount].dispatcherID = dispatchers[i].dispatcherID;
            			completedOrders[completedOrderCount].totalTime = orderQueue[k]->prepTime + orderQueue[k]->deliveryDistance;
            			completedOrderCount++;
            			break;
        			}
    			}
    			dispatchers[i].isAvailable = 1;
    			dispatchers[i].currentOrderID = -1;
			}
        }
    }
}

// View all orders
void viewOrders() {
    printf("\n--- Orders in Queue ---\n");
    for (int i = 0; i < orderCount; i++) {
        printf("OrderID: %d, Priority: %d, Assigned: %s\n",
               orderQueue[i]->orderID,
               orderQueue[i]->priority,
               orderQueue[i]->assigned == 0 ? "No" :(orderQueue[i]->assigned == 1 ? "Yes" : "Completed"));
    }
}

// View dispatcher status
void viewDispatchers() {
    printf("\n--- Dispatcher Status ---\n");
    for (int i = 0; i < MAX_DISPATCHERS; i++) {
        printf("Dispatcher %d - %s",
               dispatchers[i].dispatcherID,
               dispatchers[i].isAvailable ? "Available\n" : "Busy\n");
        if (!dispatchers[i].isAvailable) {
            printf("    Handling Order ID: %d, Remaining Time: %d\n",
                   dispatchers[i].currentOrderID,
                   dispatchers[i].remainingTime);
        }
    }
}
