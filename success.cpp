#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent bus schedule
struct BusSchedule {
    int busID;
    char source[50];
    char destination[50];
    int availableSeats;
    int fare;
};

// Structure to represent booking information
struct Booking {
    int bookingID;
    int busID;
    int seatsBooked;
};
//structure to represent employee information
   struct employee{
	char userName[50];
	char password[20];
   };

// Function declarations
void employeeSignUp();
void employeeLogin();
void addBusSchedule();
void deleteBusSchedule();
void viewAllBusSchedules();
void searchBuses();
void viewAvailableSeats(int busID);
void bookSeats(int busID);
void issueTicket(int busID, int seatsBooked);
void cancelBooking();
void viewBookingHistory();
void saveData();
void loadData();

// Global variables
struct employee employees[100];
struct BusSchedule busSchedules[100];
struct Booking bookings[100];
int numBusSchedules = 0;
int numBookings = 0;
int mumEmployees = 0;
bool isAuthenticated = false;


int main() {
    loadData(); // Load data from the file

    int choice;
    int busID;
    do {
         printf("\nBus Reservation System\n");

        // Display the authentication menu or the main menu based on the isAuthenticated flag
        if (isAuthenticated) {
            printf("3. Add Bus Schedule\n");
            printf("4. Delete Bus Schedule\n");
            printf("5. View All Bus Schedules\n");
            printf("6. Search Buses\n");
        } else {
            printf("1. Employee Signup\n");
            printf("2. Employee Login\n");
        }
        
        printf("7. View Available Seats\n");
        printf("8. Book Seats\n");
        printf("9. Issue Ticket\n");
        printf("10. Cancel Booking\n");
        printf("11. View Booking History\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        	case 1:
        		employeeSignUp();
        		break;
            case 2:
                employeeLogin();
                break;
            case 3:
                addBusSchedule();
                break;
            case 4:
                deleteBusSchedule();
                break;
            case 5:
                viewAllBusSchedules();
                break;
            case 6:
                searchBuses();
                break;
            case 7:
    			printf("Enter Bus ID to view available seats: ");
    			scanf("%d", &busID);
    			viewAvailableSeats(busID);
    			break;
            case 8:
    			printf("Enter Bus ID to book seats: ");
    			scanf("%d", &busID);
    			bookSeats(busID);
                break;
            case 9:
    			printf("Enter Bus ID to issue ticket: ");
			    scanf("%d", &busID);
			    printf("Enter number of seats booked: ");
			    int seatsBooked;
			    scanf("%d", &seatsBooked);
			    issueTicket(busID, seatsBooked);
			    break;
            case 10:
                cancelBooking();
                break;
            case 11:
                viewBookingHistory();
                break;
            case 12:
                saveData(); // Save data to the file before exiting
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}
void employeeSignUp() {
    // Allow an employee to sign up
    int numEmployees = 0;
    printf("Enter username: ");
    scanf("%s", employees[numEmployees].userName);
    printf("Enter password: ");
    scanf("%s", employees[numEmployees].password);
    numEmployees++;
    isAuthenticated=true;
    printf("Employee sign up successful!\n");
}
void employeeLogin() {
    // Add your employee login logic here
    // For simplicity, you can just print a message for successful login
    printf("Employee login successful!\n");
}

void addBusSchedule() {
    // Add new bus schedule
    printf("Enter source: ");
    scanf("%s", busSchedules[numBusSchedules].source);
    printf("Enter destination: ");
    scanf("%s", busSchedules[numBusSchedules].destination);
    printf("Enter available seats: ");
    scanf("%d", &busSchedules[numBusSchedules].availableSeats);
    printf("Enter Bus fsre: ");
    scanf("%d", &busSchedules[numBusSchedules].fare);

    busSchedules[numBusSchedules].busID = numBusSchedules + 1;
    numBusSchedules++;
    printf("Bus schedule added successfully!\n");
}

void deleteBusSchedule() {
    // Delete existing bus schedule
    int busID;
    printf("Enter Bus ID to delete: ");
    scanf("%d", &busID);

    int i;
    for (i = 0; i < numBusSchedules; i++) {
        if (busSchedules[i].busID == busID) {
            // Shift remaining schedules to fill the gap
            for (int j = i; j < numBusSchedules - 1; j++) {
                busSchedules[j] = busSchedules[j + 1];
            }
            numBusSchedules--;
            printf("Bus schedule deleted successfully!\n");
            return;
        }
    }

    printf("Bus schedule not found.\n");
}

void viewAllBusSchedules() {
	
    // View a list of all bus schedules
    printf("Bus Schedules:\n");
    for (int i = 0; i < numBusSchedules; i++) {
        printf("Bus ID: %d, Source: %s, Destination: %s, Available Seats: %d\n",
               busSchedules[i].busID, busSchedules[i].source, busSchedules[i].destination,
               busSchedules[i].availableSeats);
    }
}

void searchBuses() {
    // Search buses based on source and destination
    char source[50], destination[50];
    printf("Enter source: ");
    scanf("%s", source);
    printf("Enter destination: ");
    scanf("%s", destination);

    printf("Matching Buses:\n");
    for (int i = 0; i < numBusSchedules; i++) {
        if (strcmp(busSchedules[i].source, source) == 0 && strcmp(busSchedules[i].destination, destination) == 0) {
            printf("Bus ID: %d, Source: %s, Destination: %s, Available Seats: %d\n",
                   busSchedules[i].busID, busSchedules[i].source, busSchedules[i].destination,
                   busSchedules[i].availableSeats);
        }
    }
}
void viewAvailableSeats(int busID) {
    int i;
    for (i = 0; i < numBusSchedules; i++) {
        if (busSchedules[i].busID == busID) {
            printf("Bus ID: %d\n", busSchedules[i].busID);
            printf("Available Seats: %d\n", busSchedules[i].availableSeats);
            return;
        }
    }

    printf("Bus not found.\n");
}

void bookSeats(int busID) {
    int numSeats;
    printf("Enter the number of seats to book: ");
    scanf("%d", &numSeats);

    // Find the bus schedule based on busID
    int i;
    for (i = 0; i < numBusSchedules; i++) {
        if (busSchedules[i].busID == busID) {
            // Check if there are enough available seats
            if (numSeats <= busSchedules[i].availableSeats) {
                // Create a new booking
                bookings[numBookings].bookingID = numBookings + 1;
                bookings[numBookings].busID = busID;
                bookings[numBookings].seatsBooked = numSeats;

                // Update available seats in the bus schedule
                busSchedules[i].availableSeats -= numSeats;

                numBookings++;
                printf("Seats booked successfully!\n");
            } else {
                printf("Not enough available seats. Please choose a smaller number.\n");
            }
            return;
        }
    }

    printf("Bus not found.\n");
}

void issueTicket(int busID, int seatsBooked) {
    // Issue a ticket for the booked seats
    if (busID <= 0 || busID > numBusSchedules) {
        printf("Invalid Bus ID.\n");
        return;
    }

    if (seatsBooked <= 0) {
        printf("Invalid number of seats.\n");
        return;
    }

    // Check if there are enough available seats
    int index = -1;
    for (int i = 0; i < numBusSchedules; i++) {
        if (busSchedules[i].busID == busID) {
            if (busSchedules[i].availableSeats >= seatsBooked) {
                index = i;
                break;
            } else {
                printf("Not enough available seats for the booking.\n");
                return;
            }
        }
    }

    // Update available seats and record the booking
    busSchedules[index].availableSeats -= seatsBooked;
    bookings[numBookings].bookingID = numBookings + 1;
    bookings[numBookings].busID = busID;
    bookings[numBookings].seatsBooked = seatsBooked;
    numBookings++;

    printf("Ticket issued successfully!\n");
}





void cancelBooking() {
    // Cancel a booking
    int bookingID;
    printf("Enter Booking ID to cancel: ");
    scanf("%d", &bookingID);

    int i;
    for (i = 0; i < numBookings; i++) {
        if (bookings[i].bookingID == bookingID) {
            // Add back the booked seats to the available seats of the corresponding bus
            int busID = bookings[i].busID;
            for (int j = 0; j < numBusSchedules; j++) {
                if (busSchedules[j].busID == busID) {
                    busSchedules[j].availableSeats += bookings[i].seatsBooked;
                    break;
                }
            }

            // Shift remaining bookings to fill the gap
            for (int j = i; j < numBookings - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            numBookings--;
            printf("Booking canceled successfully!\n");
            return;
        }
    }

    printf("Booking not found.\n");
}

// Implement the remaining functions (viewAvailableSeats, bookSeats, issueTicket, cancelBooking, viewBookingHistory) based on your requirements

void viewBookingHistory() {
    // View booking history of all bookings made
    printf("Booking History:\n");
    for (int i = 0; i < numBookings; i++) {
        printf("Booking ID: %d, Bus ID: %d, Seats Booked: %d\n",
               bookings[i].bookingID, bookings[i].busID, bookings[i].seatsBooked);
    }
}

void saveData() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    // Save bus schedules
    fprintf(file, "Bus Schedules:\n");
    for (int i = 0; i < numBusSchedules; i++) {
        fprintf(file, "%d %s %s %d\n", busSchedules[i].busID, busSchedules[i].source, busSchedules[i].destination,
                busSchedules[i].availableSeats);
    }

    // Save bookings
    fprintf(file, "Bookings:\n");
    for (int i = 0; i < numBookings; i++) {
        fprintf(file, "%d %d %d\n", bookings[i].bookingID, bookings[i].busID, bookings[i].seatsBooked);
    }

    fclose(file);
}

void loadData() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        // File does not
	}}
