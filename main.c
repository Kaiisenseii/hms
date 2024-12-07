#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "staff.h"
#include "customer.h"
#include "common.h"
#include "guest.h"

int main() {
    int role;

    while (1) {
        printf("\nWelcome to the Hotel Management System\n");
        printf("1. Administrator\n2. Hotel Staff\n3. Customer\n4. Guest\n5. Exit\n");
        printf("Enter your role (1-5): ");

        role = getValidatedInput(1, 5);

        switch (role) {
            case 1:
                adminMenu();
                break;
            case 2:
                staffMenu();
                break;
            case 3:
                customerMenu();
                break;
            case 4:
                guestMenu();
                break;
            case 5:
                printf("Exiting the system.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}