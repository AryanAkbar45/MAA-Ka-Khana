#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ===============================
// FUNCTION DECLARATIONS
// ===============================
void signup();
int login();
void menu();
void takeOrder();
void generateBill();

// ===============================
// GLOBAL ARRAYS FOR MENU
// ===============================

// Desi food items including Chai
char items[][60] = {
    "Chicken Biryani",
    "Chicken Karahi",
    "Beef Nihari",
    "Chicken Qorma",
    "Pulao",
    "Daal Chawal",
    "Chai",
    "Family Deal"
};

// Prices of each food item
int prices[] = {250, 1200, 300, 200, 180, 120, 80, 3500};

// Array to store quantity selected by customer
int quantity[10] = {0};

// ===============================
// MAIN FUNCTION
// ===============================
int main() {
    int choice;

    printf("\n\n======= WELCOME TO MAA KA KHANA RESTAURANT =======\n");

    while(1) {
        printf("\n1. Signup\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                signup();
                break;
            case 2:
                if(login()) {
                    printf("\nLogin Successful!\n");
                    takeOrder();
                } else {
                    printf("\nWrong Username or Password!\n");
                }
                break;
            case 3:
                printf("\nThank you for visiting MAA KA KHANA!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// ===============================
// SIGNUP FUNCTION
// ===============================
void signup() {
    char username[50], password[50];
    FILE *fp;

    printf("\nEnter new username: ");
    scanf("%s", username);

    printf("Enter new password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "a");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("\nSignup Successful!\n");
}

// ===============================
// LOGIN FUNCTION
// ===============================
int login() {
    char username[50], password[50], u[50], p[50];
    FILE *fp;

    printf("\nEnter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "r");
    if(fp == NULL) {
        printf("No users found! Please signup first.\n");
        return 0;
    }

    while(fscanf(fp, "%s %s", u, p) != EOF) {
        if(strcmp(username, u) == 0 && strcmp(password, p) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// ===============================
// SHOW MENU FUNCTION
// ===============================
void menu() {
    printf("\n===== MAA KA KHANA MENU =====\n");

    for(int i = 0; i < 8; i++) {
        printf("%d. %s - Rs %d\n", i+1, items[i], prices[i]);
    }
}

// ===============================
// ORDER FUNCTION
// ===============================
void takeOrder() {
    int choice, qty;

    while(1) {
        menu();

        printf("\nSelect item number (0 to finish order): ");
        scanf("%d", &choice);

        if(choice == 0) {
            generateBill();
            break;
        }

        if(choice < 1 || choice > 8) {
            printf("\nInvalid item!\n");
        } else {
            printf("Enter quantity: ");
            scanf("%d", &qty);

            quantity[choice-1] += qty;
            printf("\nAdded to order!\n");
        }
    }
}

// ===============================
// BILL PRINT FUNCTION
// ===============================
void generateBill() {
    int total = 0;

    printf("\n\n======= FINAL BILL (MAA KA KHANA) =======\n");
    printf("Items\t\tQty\tPrice\tTotal\n");
    printf("------------------------------------------\n");

    for(int i = 0; i < 8; i++) {
        if(quantity[i] > 0) {
            int itemTotal = quantity[i] * prices[i];
            printf("%s\t%d\t%d\t%d\n",
                   items[i], quantity[i], prices[i], itemTotal);
            total += itemTotal;
        }
    }

    // 5% SERVICE CHARGE
    int serviceCharge = (total * 5) / 100;
    int grandTotal = total + serviceCharge;

    printf("------------------------------------------\n");
    printf("Subtotal:\t\t\t%d\n", total);
    printf("Service Charge (5%%):\t\t%d\n", serviceCharge);
    printf("------------------------------------------\n");
    printf("Grand Total:\t\t\t%d\n", grandTotal);
    printf("\nThank you for dining at MAA KA KHANA!\n\n");
}
