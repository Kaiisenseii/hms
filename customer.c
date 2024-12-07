#include <stdio.h>
#include "customer.h"
#include "common.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

int isValidDate(char *date) {
    // Check the format YYYY-MM-DD
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
        return 0;
    }

    // Extract year, month, and day
    char yearStr[5], monthStr[3], dayStr[3];
    strncpy(yearStr, date, 4);
    yearStr[4] = '\0';
    strncpy(monthStr, date + 5, 2);
    monthStr[2] = '\0';
    strncpy(dayStr, date + 8, 2);
    dayStr[2] = '\0';

    // Check if year, month, and day are numeric
    if (!isdigit(yearStr[0]) || !isdigit(yearStr[1]) || !isdigit(yearStr[2]) || !isdigit(yearStr[3]) ||
        !isdigit(monthStr[0]) || !isdigit(monthStr[1]) || !isdigit(dayStr[0]) || !isdigit(dayStr[1])) {
        return 0;
    }

    int year = atoi(yearStr);
    int month = atoi(monthStr);
    int day = atoi(dayStr);

    // Validate year range
    if (year < 1900 || year > 2100) {
        return 0;
    }

    // Validate month
    if (month < 1 || month > 12) {
        return 0;
    }

    // Validate day based on month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29; // Leap year
    }
    if (day < 1 || day > daysInMonth[month - 1]) {
        return 0;
    }

    return 1; // Valid date
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

    // Validate check-in date
    while (1) {
        printf("Enter Check-in Date (YYYY-MM-DD): ");
        scanf("%s", checkInDate);
        if (isValidDate(checkInDate)) {
            break;
        } else {
            printf("Invalid date format. Please enter a valid date in YYYY-MM-DD format.\n");
        }
    }

    // Validate check-out date
    while (1) {
        printf("Enter Check-out Date (YYYY-MM-DD): ");
        scanf("%s", checkOutDate);
        if (isValidDate(checkOutDate)) {
            break;
        } else {
            printf("Invalid date format. Please enter a valid date in YYYY-MM-DD format.\n");
        }
    }

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
