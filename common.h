#ifndef COMMON_H
#define COMMON_H

#define MAX_USERS 100
#define MAX_ROOMS 50
#define MAX_RESERVATIONS 100

typedef struct {
    char username[30];
    char phoneNumber[15];
    char password[20];
    char role[20];
} User;

typedef struct {
    int roomNumber;
    char roomType[20];
    int isAvailable;
    float rate;
} Room;

typedef struct {
    int reservationID;
    char customerUsername[30];
    int roomNumber;
    char checkInDate[20];
    char checkOutDate[20];
} Reservation;

extern User users[MAX_USERS];
extern int userCount;

extern Room rooms[MAX_ROOMS];
extern int roomCount;

extern Reservation reservations[MAX_RESERVATIONS];
extern int reservationCount;

// Function declarations
int getValidatedInput(int min, int max);
void loadUsers();
void saveUsers();
void loadRooms();
void saveRooms();
void loadReservations();
void saveReservations();
int validateUser(const char *username, const char *password, const char *role);
void registerNewUser();

#endif