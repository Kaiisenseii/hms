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

        choice = getValidatedInput(1, 4);

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

        // Display existing rooms and their availability
        if (roomCount == 0) {
            printf("No rooms available.\n");
        } else {
            printf("\nExisting Rooms:\n");
            for (int i = 0; i < roomCount; i++) {
                printf("Room Number: %d | Type: %s | Rate: $%.2f | Availability: %s\n",
                       rooms[i].roomNumber,
                       rooms[i].roomType,
                       rooms[i].rate,
                       rooms[i].isAvailable ? "Available" : "Occupied");
            }
        }

        // Menu options
        printf("\n1. Add Room\n2. Update Room\n3. Remove Room\n4. Back\n");
        printf("Enter your choice: ");
        choice = getValidatedInput(1, 4);
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

    while (1) {
        printf("Enter Room Type (Lux/Basic/Common/DoubleBed): ");
        scanf("%s", rooms[roomCount].roomType);

        // Validate the room type
        if (strcmp(rooms[roomCount].roomType, "Lux") == 0 || 
            strcmp(rooms[roomCount].roomType, "Basic") == 0 || 
            strcmp(rooms[roomCount].roomType, "Common") == 0 || 
            strcmp(rooms[roomCount].roomType, "DoubleBed") == 0) {
            break; // Valid input, exit loop
        } else {
            printf("Invalid room type. Please enter one of the following: Lux, Basic, Common, DoubleBed.\n");
        }
    }

    printf("Enter Room Rate: ");
    scanf("%f", &rooms[roomCount].rate);

    while (1) {
        char availability[20];
        printf("Enter Room Availability (Available/Occupied): ");
        scanf("%s", availability);

        // Validate availability
        if (strcmp(availability, "Available") == 0) {
            rooms[roomCount].isAvailable = 1;
            break;
        } else if (strcmp(availability, "Occupied") == 0) {
            rooms[roomCount].isAvailable = 0;
            break;
        } else {
            printf("Invalid availability. Please enter 'Available' or 'Occupied'.\n");
        }
    }

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
            while (1) {
                printf("Enter New Room Type (Lux/Basic/Common/DoubleBed): ");
                scanf("%s", rooms[i].roomType);

                // Validate the room type
                if (strcmp(rooms[i].roomType, "Lux") == 0 || 
                    strcmp(rooms[i].roomType, "Basic") == 0 || 
                    strcmp(rooms[i].roomType, "Common") == 0 || 
                    strcmp(rooms[i].roomType, "DoubleBed") == 0) {
                    break; // Valid input, exit loop
                } else {
                    printf("Invalid room type. Please enter one of the following: Lux, Basic, Common, DoubleBed.\n");
                }
            }

            printf("Enter New Room Rate: ");
            scanf("%f", &rooms[i].rate);

            while (1) {
                char availability[20];
                printf("Enter New Room Availability (Available/Occupied): ");
                scanf("%s", availability);

                // Validate availability
                if (strcmp(availability, "Available") == 0) {
                    rooms[i].isAvailable = 1;
                    break;
                } else if (strcmp(availability, "Occupied") == 0) {
                    rooms[i].isAvailable = 0;
                    break;
                } else {
                    printf("Invalid availability. Please enter 'Available' or 'Occupied'.\n");
                }
            }

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

