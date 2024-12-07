#include <stdio.h>
#include <string.h>
#include "common.h"

User users[MAX_USERS];
int userCount = 0;

Room rooms[MAX_ROOMS];
int roomCount = 0;

Reservation reservations[MAX_RESERVATIONS];
int reservationCount = 0;

void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return;
    userCount = 0;
    while (fscanf(file, "%s %s %s %s", users[userCount].username, users[userCount].phoneNumber, users[userCount].password, users[userCount].role) == 4) {
        userCount++;
    }
    fclose(file);
}

void saveUsers() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %s %s\n", users[i].username, users[i].phoneNumber, users[i].password, users[i].role);
    }
    fclose(file);
}

void loadRooms() {
    FILE *file = fopen("rooms.txt", "r");
    if (file == NULL) return;
    roomCount = 0;
    while (fscanf(file, "%d %s %d %f", &rooms[roomCount].roomNumber, rooms[roomCount].roomType, &rooms[roomCount].isAvailable, &rooms[roomCount].rate) == 4) {
        roomCount++;
    }
    fclose(file);
}

void saveRooms() {
    FILE *file = fopen("rooms.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < roomCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", rooms[i].roomNumber, rooms[i].roomType, rooms[i].isAvailable, rooms[i].rate);
    }
    fclose(file);
}

void loadReservations() {
    FILE *file = fopen("reservations.txt", "r");
    if (file == NULL) return;
    reservationCount = 0;
    while (fscanf(file, "%d %s %d %s %s", &reservations[reservationCount].reservationID, reservations[reservationCount].customerUsername, &reservations[reservationCount].roomNumber, reservations[reservationCount].checkInDate, reservations[reservationCount].checkOutDate) == 5) {
        reservationCount++;
    }
    fclose(file);
}

void saveReservations() {
    FILE *file = fopen("reservations.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < reservationCount; i++) {
        fprintf(file, "%d %s %d %s %s\n", reservations[i].reservationID, reservations[i].customerUsername, reservations[i].roomNumber, reservations[i].checkInDate, reservations[i].checkOutDate);
    }
    fclose(file);
}

int validateUser(const char *username, const char *password, const char *role) {
    loadUsers();
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0 &&
            strcmp(users[i].role, role) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

void registerNewUser() {
    if (userCount >= MAX_USERS) {
        printf("Cannot register more users.\n");
        return;
    }

    printf("Enter Username: ");
    scanf("%s", users[userCount].username);

    printf("Enter Phone Number: ");
    scanf("%s", users[userCount].phoneNumber);

    printf("Enter Password: ");
    scanf("%s", users[userCount].password);

    while (1) {
        printf("Enter Role (Admin/Staff/Customer): ");
        scanf("%s", users[userCount].role);

        // Validate the role input
        if (strcmp(users[userCount].role, "Admin") == 0 || 
            strcmp(users[userCount].role, "Staff") == 0 || 
            strcmp(users[userCount].role, "Customer") == 0) {
            break; // Valid role, exit the loop
        } else {
            printf("Invalid role. Please enter 'Admin', 'Staff', or 'Customer' only.\n");
        }
    }

    userCount++;
    saveUsers();
    printf("User registered successfully.\n");
}
