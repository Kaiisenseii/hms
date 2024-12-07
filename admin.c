#include <stdio.h>
#include <string.h>
#include "admin.h"
#include "common.h"

void adminMenu() {
    char username[30], password[20];
    printf("\n--- Admin Login ---\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") != 0 || strcmp(password, "pass") != 0) {
        printf("Invalid admin credentials.\n");
        return;
    }

    int choice;
    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Register New User\n2. Manage Hotel Rooms\n3. View Reservations\n4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerNewUser();
                break;
            case 2:
                manageHotelRooms();
                break;
            case 3:
                viewReservations();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

void manageHotelRooms() {
    int choice;
    do {
        printf("\n--- Manage Hotel Rooms ---\n");
        printf("1. Add Room\n2. Update Room\n3. Remove Room\n4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addRoom();
                break;
            case 2:
                updateRoom();
                break;
            case 3:
                removeRoom();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

void viewReservations() {
    loadReservations();
    printf("\n--- Reservations ---\n");
    for (int i = 0; i < reservationCount; i++) {
        printf("Reservation ID: %d | Customer: %s | Room: %d | Check-In: %s | Check-Out: %s\n",
               reservations[i].reservationID, reservations[i].customerUsername,
               reservations[i].roomNumber, reservations[i].checkInDate, reservations[i].checkOutDate);
    }
}

void addRoom() {
    if (roomCount >= MAX_ROOMS) {
        printf("Cannot add more rooms.\n");
        return;
    }
    printf("Enter Room Number: ");
    scanf("%d", &rooms[roomCount].roomNumber);
    printf("Enter Room Type: ");
    scanf("%s", rooms[roomCount].roomType);
    printf("Enter Room Rate: ");
    scanf("%f", &rooms[roomCount].rate);
    rooms[roomCount].isAvailable = 1;
    roomCount++;
    saveRooms();
    printf("Room added successfully.\n");
}

void updateRoom() {
    int roomNumber;
    printf("Enter Room Number to Update: ");
    scanf("%d", &roomNumber);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            printf("Enter New Room Type: ");
            scanf("%s", rooms[i].roomType);
            printf("Enter New Room Rate: ");
            scanf("%f", &rooms[i].rate);
            saveRooms();
            printf("Room updated successfully.\n");
            return;
        }
    }
    printf("Room not found.\n");
}

void removeRoom() {
    int roomNumber;
    printf("Enter Room Number to Remove: ");
    scanf("%d", &roomNumber);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            for (int j = i; j < roomCount - 1; j++) {
                rooms[j] = rooms[j + 1];
            }
            roomCount--;
            saveRooms();
            printf("Room removed successfully.\n");
            return;
        }
    }
    printf("Room not found.\n");
}