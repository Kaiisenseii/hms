#include <stdio.h>
#include "customer.h"
#include "common.h"
#include <string.h>

void customerMenu() {
    char username[30], password[20];
    printf("\n--- Customer Login ---\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (!validateUser(username, password, "Customer")) {
        printf("Invalid customer credentials.\n");
        return;
    }

    int choice;
    do {
        printf("\n--- Customer Menu ---\n");
        printf("1. Search Rooms\n2. Make Reservation\n3. Cancel Reservation\n4. View Booking History\n5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                searchRooms();
                break;
            case 2:
                makeReservation(username);
                break;
            case 3:
                cancelReservation(username);
                break;
            case 4:
                viewBookingHistory(username);
                break;
            case 5:
                return;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

void searchRooms() {
    loadRooms();
    printf("\nAvailable Rooms:\n");
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].isAvailable) {
            printf("Room %d: %s ($%.2f)\n", rooms[i].roomNumber, rooms[i].roomType, rooms[i].rate);
        }
    }
}

void makeReservation(char *username) {
    loadRooms();
    loadReservations();

    int roomNumber, available = 0;
    char checkInDate[20], checkOutDate[20];

    printf("Enter Room Number to Reserve: ");
    scanf("%d", &roomNumber);

    // Check room availability
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber && rooms[i].isAvailable) {
            available = 1;
            break;
        }
    }

    if (!available) {
        printf("Room %d is not available.\n", roomNumber);
        return;
    }

    printf("Enter Check-in Date (YYYY-MM-DD): ");
    scanf("%s", checkInDate);
    printf("Enter Check-out Date (YYYY-MM-DD): ");
    scanf("%s", checkOutDate);

    // Create a new reservation
    reservations[reservationCount].reservationID = reservationCount + 1;
    strcpy(reservations[reservationCount].customerUsername, username);
    reservations[reservationCount].roomNumber = roomNumber;
    strcpy(reservations[reservationCount].checkInDate, checkInDate);
    strcpy(reservations[reservationCount].checkOutDate, checkOutDate);
    reservationCount++;

    // Update room availability
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            rooms[i].isAvailable = 0;
            break;
        }
    }

    saveReservations();
    saveRooms();

    printf("Reservation successful! Your Reservation ID is %d.\n", reservationCount);
}


void cancelReservation(char *username) {
     loadReservations();
    loadRooms();

    int reservationID, found = 0;

    printf("Enter Reservation ID to Cancel: ");
    scanf("%d", &reservationID);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].reservationID == reservationID &&
            strcmp(reservations[i].customerUsername, username) == 0) {
            found = 1;

            // Update room availability
            for (int j = 0; j < roomCount; j++) {
                if (rooms[j].roomNumber == reservations[i].roomNumber) {
                    rooms[j].isAvailable = 1;
                    break;
                }
            }

            // Shift reservations array
            for (int k = i; k < reservationCount - 1; k++) {
                reservations[k] = reservations[k + 1];
            }

            reservationCount--;
            saveReservations();
            saveRooms();

            printf("Reservation %d has been canceled.\n", reservationID);
            break;
        }
    }

    if (!found) {
        printf("Reservation ID not found or not associated with your account.\n");
    }
}
void viewBookingHistory(char *username) {
   loadReservations();

    printf("\n--- Booking History for %s ---\n", username);
    for (int i = 0; i < reservationCount; i++) {
        if (strcmp(reservations[i].customerUsername, username) == 0) {
            printf("Reservation ID: %d, Room %d, Check-in: %s, Check-out: %s\n",
                   reservations[i].reservationID, reservations[i].roomNumber,
                   reservations[i].checkInDate, reservations[i].checkOutDate);
        }
    }
}
