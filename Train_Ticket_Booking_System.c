#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 10
#define MAX_TRAINS 10

// Seat structure
struct Seat{
    int seatNumber;
    int isBooked;
};

int numPsg;
int allocatedSeats[MAX_SEATS];

// Structure - train information
struct Train {
    int trainNumber;
    char source[30];
    char destination[30];
    struct Seat slSeats[MAX_SEATS];  // Sleeper coach seats
    struct Seat acSeats[MAX_SEATS];  // AC coach seats
    int slPrice;  // Price for SL seat
    int acPrice;  // Price for AC seat
    int general;  // Price for General seat
    char available[50];
    char dptime[10];
};


// Train data
void initializeTrains(Train trains[]) {
    // Train 1
    trains[0].trainNumber = 16536;
    strcpy(trains[0].source, "Davanagere");
    strcpy(trains[0].destination, "Mysuru");
    trains[0].slPrice = 100;  // Price for Sleeper
    trains[0].acPrice = 250;  // Price for AC
    trains[0].general = 70;   // Price for General
    strcpy(trains[0].available, "Runs Daily");
    strcpy(trains[0].dptime, "02:31 PM");
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[0].slSeats[i].seatNumber = i + 1;
        trains[0].slSeats[i].isBooked = 0;
        trains[0].acSeats[i].seatNumber = i + 1;
        trains[0].acSeats[i].isBooked = 0;
    }

    // Train 2
    trains[1].trainNumber = 17302;
    strcpy(trains[1].source, "Davanagere");
    strcpy(trains[1].destination, "Mysuru");
    trains[1].slPrice = 120;
    trains[1].acPrice = 300;
    strcpy(trains[1].available, "Runs Daily");
    trains[1].general = 70;
    strcpy(trains[1].dptime, "11:57 PM");
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[1].slSeats[i].seatNumber = i + 1;
        trains[1].slSeats[i].isBooked = 0;
        trains[1].acSeats[i].seatNumber = i + 1;
        trains[1].acSeats[i].isBooked = 0;
    }

    // Train 3
    trains[2].trainNumber = 11035;
    strcpy(trains[2].source, "Davanagere");
    strcpy(trains[2].destination, "Mysuru");
    trains[2].slPrice = 110;
    trains[2].acPrice = 270;
    strcpy(trains[2].available, "Friday");
    strcpy(trains[2].dptime, "03:25 PM");
    trains[2].general = 70;
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[2].slSeats[i].seatNumber = i + 1;
        trains[2].slSeats[i].isBooked = 0;
        trains[2].acSeats[i].seatNumber = i + 1;
        trains[2].acSeats[i].isBooked = 0;
    }

    // Train 4
    trains[3].trainNumber = 16535;
    strcpy(trains[3].source, "Mysuru");
    strcpy(trains[3].destination, "Davanagere");
    trains[3].slPrice = 115;
    trains[3].acPrice = 280;
    strcpy(trains[3].available, "Runs Daily");
    strcpy(trains[3].dptime, "03:45 PM");
    trains[3].general = 70;
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[3].slSeats[i].seatNumber = i + 1;
        trains[3].slSeats[i].isBooked = 0;
        trains[3].acSeats[i].seatNumber = i + 1;
        trains[3].acSeats[i].isBooked = 0;
    }

    // Train 5
    trains[4].trainNumber = 16210;
    strcpy(trains[4].source, "Mysuru");
    strcpy(trains[4].destination, "Davanagere");
    trains[4].slPrice = 130;
    trains[4].acPrice = 320;
    strcpy(trains[4].available, "Tuesday, Thursday");
    strcpy(trains[4].dptime, "07:10 PM");
	trains[4].general = 70;
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[4].slSeats[i].seatNumber = i + 1;
        trains[4].slSeats[i].isBooked = 0;
        trains[4].acSeats[i].seatNumber = i + 1;
        trains[4].acSeats[i].isBooked = 0;
    }
    
    //Train 6
    trains[5].trainNumber = 20655;
    strcpy(trains[5].source, "Tumakuru");
    strcpy(trains[5].destination, "Davanagere");
    trains[5].slPrice = 100;  // Price for Sleeper
    trains[5].acPrice = 250;  // Price for AC
    trains[5].general = 70;
    strcpy(trains[5].available, "Saturday");
    strcpy(trains[5].dptime, "12:40 AM");
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[5].slSeats[i].seatNumber = i + 1;
        trains[5].slSeats[i].isBooked = 0;
        trains[5].acSeats[i].seatNumber = i + 1;
        trains[5].acSeats[i].isBooked = 0;
    }
    
    // Train 7
    trains[6].trainNumber = 07377;
    strcpy(trains[6].source, "Davanagere");
    strcpy(trains[6].destination, "Mangaluru");
    trains[6].slPrice = 100;  // Price for Sleeper
    trains[6].acPrice = 250;  // Price for AC
    trains[6].general = 70;
    strcpy(trains[6].available, "Runs Daily");
    strcpy(trains[6].dptime, "11:45 PM");
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[6].slSeats[i].seatNumber = i + 1;
        trains[6].slSeats[i].isBooked = 0;
        trains[6].acSeats[i].seatNumber = i + 1;
        trains[6].acSeats[i].isBooked = 0;
    }

    // Train 8
    trains[7].trainNumber = 12726;
    strcpy(trains[7].source, "Davanagere");
    strcpy(trains[7].destination, "Arsikere");
    trains[7].slPrice = 120;
    trains[7].acPrice = 300;
    strcpy(trains[7].available, "Runs Daily");
    strcpy(trains[7].dptime, "08:20 PM");
    trains[7].general = 70;
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[7].slSeats[i].seatNumber = i + 1;
        trains[7].slSeats[i].isBooked = 0;
        trains[7].acSeats[i].seatNumber = i + 1;
        trains[7].acSeats[i].isBooked = 0;
    }

    // Train 9
    trains[8].trainNumber = 11035;
    strcpy(trains[8].source, "Davanagere");
    strcpy(trains[8].destination, "Hassan");
    trains[8].slPrice = 110;
    trains[8].acPrice = 270;
    strcpy(trains[8].available, "Friday");
    strcpy(trains[8].dptime, "03:25 PM");
    trains[8].general = 70;
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[8].slSeats[i].seatNumber = i + 1;
        trains[8].slSeats[i].isBooked = 0;
        trains[8].acSeats[i].seatNumber = i + 1;
        trains[8].acSeats[i].isBooked = 0;
    }

    // Train 10
    trains[9].trainNumber = 17391;
    strcpy(trains[9].source, "Tumakuru");
    strcpy(trains[9].destination, "Davanagere");
    trains[9].slPrice = 115;
    trains[9].acPrice = 280;
    strcpy(trains[9].available, "Runs Daily");
    strcpy(trains[9].dptime, "01:23 AM");
    trains[9].general = 70;
    for (int i = 0; i < MAX_SEATS; i++) {
        trains[9].slSeats[i].seatNumber = i + 1;
        trains[9].slSeats[i].isBooked = 0;
        trains[9].acSeats[i].seatNumber = i + 1;
        trains[9].acSeats[i].isBooked = 0;
    }

}


// Display available trains
int  displayTrains(Train trains[], int numTrains, char source[], char destination[]) {
    printf("\nAvailable trains from %s to %s:\n", source, destination);
    int found = 0;
    for (int i = 0; i < numTrains; i++) {
        if (strcmp(trains[i].source, source) == 0 && strcmp(trains[i].destination, destination) == 0) {
            printf("Train Number: %d | Source: %s | Destination: %s | Deaparture Time: %s | %s\n", trains[i].trainNumber, trains[i].source, trains[i].destination, trains[i].dptime, trains[i].available);
            found = 1;
        }
    }
    if (!found) {
        printf("No trains available for the selected route.\n");
        return -1;
    }
    return 0;
}


// Seats with prices
void displaySeatTypes(Train *train) {
    printf("\nAvailable Seat Types:\n");
    printf("1. Sleeper Class (SL) - Price: %d\n", train->slPrice);
    printf("2. Air Conditioned (AC) - Price: %d\n", train->acPrice);
    printf("3. General (No need to book) - Price: %d\n", train->general);
}


// Book a seat 
int bookSeats(Train *train, int seatType) {
    Seat *seats = (seatType == 1) ? train->slSeats : train->acSeats;
    int totalSeats = MAX_SEATS;
    int bookedCount = 0, allocatedIndex=0;
	
	printf("Enter the number of passangers : ");
	scanf("%d", &numPsg);
	
    for (int i = 0; i < totalSeats; i++) {
        if (seats[i].isBooked == 0) {
            seats[i].isBooked = 1;
            allocatedSeats[allocatedIndex++] = seats[i].seatNumber;
            bookedCount++;
            if (bookedCount == numPsg) {
                return 1;  
            }
        }
    }

    printf("Sorry, not enough seats available for %d passengers.\n", numPsg);
    return 0;
}


// Generate the ticket
void generateTicket(Train *train, int seatNumber, char seatType[], char name[], char journeyDate[]) {
	int pricePerSeat = (strcmp(seatType, "Sleeper Class (SL)") == 0) ? train->slPrice: train->acPrice;
	int totalPrice = numPsg*pricePerSeat;
	
	printf("\n\n\n--- --- --- --- TICKET GENERATED --- --- --- ---\n\n");
    printf("Name:           %s\n", name);
    printf("Journey Date:   %s\n", journeyDate);
    printf("Train Number:   %d\n", train->trainNumber);
    printf("Source:         %s\n", train->source);
    printf("Destination:    %s\n", train->destination);
    printf("Number of passangers: %d\n", numPsg);
    printf("Price per seat: %d\n", pricePerSeat);
    printf("Total Price:    %d\n", totalPrice);
    printf("Seat Type:      %s\n", seatType);
    printf("Departure Time: %s\n", train->dptime);
    
    printf("Allocated seat numbers : ");
    for(int i=0;i<numPsg; i++){
    	printf("S%d  ", allocatedSeats[i]);
	}
	printf("\n");
	printf("\n--- --- --- --- HAPPY JOURNEY --- --- --- ---\n\n");
}

void BookTicket(Train *trains) {
    printf("\nEnter the details again \n\n");
    char source[30], destination[30], name[50], journeyDate[20];
    int trainNumber, seatType, seatNumber;

    // User inputs source and destination
    printf("Enter your source station: ");
    scanf("%s", source);
    printf("Enter your destination station: ");
    scanf("%s", destination);

    // Display available trains
   int ta = displayTrains(trains, MAX_TRAINS, source, destination);
   if(ta==-1)
   		return;

    // User selects the train number
    printf("\nEnter the train number to book a seat: ");
    scanf("%d", &trainNumber);

    // Check if the train is available
    int trainIndex = -1;
    for (int i = 0; i < MAX_TRAINS; i++) {
        if (trains[i].trainNumber == trainNumber) {
            trainIndex = i;
            break;
        }
    }

    if (trainIndex == -1) {
        printf("Train is not available on this route. Exiting.\n");
        return ;
    }

    // User inputs name and journey date
    printf("Enter your name: ");
    scanf(" %[^\n]%*c", name);
    printf("Enter your journey date (DD/MM/YYYY): ");
    scanf(" %[^\n]%*c", journeyDate);

    // Display seat types (SL and AC)
    displaySeatTypes(&trains[trainIndex]);

    // User selects seat type
    printf("\nChoose the seat type (1 for SL, 2 for AC): ");
    scanf("%d", &seatType);

    if (seatType == 1) {
        // Book SL seat
        bookSeats(&trains[trainIndex], 1);
        seatNumber = trainNumber;
        generateTicket(&trains[trainIndex], seatNumber, "Sleeper Class (SL)", name, journeyDate);
    } else if (seatType == 2) {
        // Book AC seat
        bookSeats(&trains[trainIndex], 2);
        seatNumber = trainNumber;
        generateTicket(&trains[trainIndex], seatNumber, "Air Conditioned (AC)", name, journeyDate);
    } else {
        printf("Invalid seat type selected.\n");
    }

}


void checkTrain(Train *trains){

    char source[30], destination[30], name[50], journeyDate[20];
    int trainNumber, seatType, seatNumber;
	int choice;
	
    // User inputs source and destination
    printf("Enter your source station: ");
    scanf("%s", source);
    printf("Enter your destination station: ");
    scanf("%s", destination);

    // Display available trains
    displayTrains(trains, MAX_TRAINS, source, destination);
	
	//Options
	while(1){
		printf("\n\nEnter the choice to proceed further :\n");
		printf("1. To Book Ticket\n");
		printf("2. To check trains again\n");
		printf("0. To exit\n");
		printf("Enter : ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:BookTicket(trains);
				break;
			
			case 2:checkTrain(trains);
				break;
				
			case 0:printf("... ... ... ..Thank you.. ... ... ...\n");
			exit(1);
			
			default:printf("Invalid choice...\n");
		}
	}	
}

int main(){
	
	Train trains[MAX_TRAINS];
    initializeTrains(trains);

	printf("----- ----- ----- WELCOME ----- ----- -----\n\n");
	checkTrain(trains);
	return 0;
}
