#include <stdio.h>
#include "staff.h"
#include "common.h"

void staffMenu() {
     char username[30], password[20];
    printf("\n--- Staff Login ---\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (!validateUser(username, password, "Staff")) {
        printf("Invalid staff credentials.\n");
        return;
    }

    int choice;
    do {
        printf("\n--- Staff Menu ---\n");
        printf("1. Manage Reservations\n");
        printf("2. Check In/Out Guests\n");
        printf("3. View Room Availability\n");
        printf("4. View Booking History\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        
        choice = getValidatedInput(1, 5);

        switch (choice) {
            case 1:
                manageReservations();
                break;
            case 2:
                checkInOutGuests();
                break;
            case 3:
                viewRoomAvailability();
                break;
            case 4:
                staffViewBookingHistory(); // Updated function name
                break;
            case 5:
                return;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
void manageReservations() {
    loadReservations();

    printf("\n--- All Reservations ---\n");
    for (int i = 0; i < reservationCount; i++) {
        printf("Reservation ID: %d, Customer: %s, Room: %d, Check-in: %s, Check-out: %s\n",
               reservations[i].reservationID, reservations[i].customerUsername,
               reservations[i].roomNumber, reservations[i].checkInDate,
               reservations[i].checkOutDate);
    }
}
void checkInGuest() {
    loadReservations();
    loadRooms();

    int reservationID, found = 0;

    printf("Enter Reservation ID for Check-in: ");
    scanf("%d", &reservationID);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].reservationID == reservationID) {
            found = 1;

            // Verify if room is already booked
            for (int j = 0; j < roomCount; j++) {
                if (rooms[j].roomNumber == reservations[i].roomNumber) {
                    if (rooms[j].isAvailable == 0) {
                        printf("Guest checked in successfully for Reservation ID: %d.\n", reservationID);
                    } else {
                        printf("Room %d was not reserved. Please check.\n", reservations[i].roomNumber);
                        rooms[j].isAvailable = 0; // Update room to occupied
                    }
                    break;
                }
            }
            saveRooms();
            break;
        }
    }

    if (!found) {
        printf("Reservation ID not found.\n");
    }
}
// Function to check out a guest
void checkOutGuest() {
    loadReservations();
    loadRooms();

    int reservationID, found = 0;

    printf("Enter Reservation ID for Check-out: ");
    scanf("%d", &reservationID);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].reservationID == reservationID) {
            found = 1;

            // Update room availability
            for (int j = 0; j < roomCount; j++) {
                if (rooms[j].roomNumber == reservations[i].roomNumber) {
                    rooms[j].isAvailable = 1;
                    break;
                }
            }
            saveRooms();
            printf("Guest checked out successfully for Reservation ID: %d.\n", reservationID);
            break;
        }
    }

    if (!found) {
        printf("Reservation ID not found.\n");
    }
}
void checkInOutGuests() {
    int choice;

    do {
        printf("\n--- Check In/Out Menu ---\n");
        printf("1. Check In Guest\n2. Check Out Guest\n3. Back to Staff Menu\n");
        printf("Enter your choice: ");
        
        choice = getValidatedInput(1, 3);

        switch (choice) {
            case 1:
                checkInGuest();
                break;
            case 2:
                checkOutGuest();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);
}


void viewRoomAvailability() {
    loadRooms();
    printf("\nRoom Availability:\n");
    for (int i = 0; i < roomCount; i++) {
        printf("Room %d: %s\n", rooms[i].roomNumber, rooms[i].isAvailable ? "Available" : "Occupied");
    }
}

void staffViewBookingHistory() { 
    loadReservations(); // Load all reservations from storage

    printf("\n--- Booking History ---\n");
    if (reservationCount == 0) {
        printf("No bookings available.\n");
        return;
    }

    for (int i = 0; i < reservationCount; i++) {
        printf("Reservation ID: %d\n", reservations[i].reservationID);
        printf("Customer Username: %s\n", reservations[i].customerUsername);
        printf("Room Number: %d\n", reservations[i].roomNumber);
        printf("Check-in Date: %s\n", reservations[i].checkInDate);
        printf("Check-out Date: %s\n\n", reservations[i].checkOutDate);
    }
}