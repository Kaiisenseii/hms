#include <stdio.h>
#include "guest.h"
#include "common.h"

void guestMenu() {
    printf("\n--- Guest Menu ---\n");
    viewRoomDetails();
}

void viewRoomDetails() {
    loadRooms(); // Load room data
    printf("\nRoom Details:\n");
    for (int i = 0; i < roomCount; i++) {
        printf("Room %d: %s ($%.2f) - %s\n",
               rooms[i].roomNumber,
               rooms[i].roomType,
               rooms[i].rate,
               rooms[i].isAvailable ? "Available" : "Occupied");
    }
}