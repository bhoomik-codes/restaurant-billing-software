#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_NAME_LENGTH 100

// Structure to hold bill information
typedef struct {
    char customerName[MAX_NAME_LENGTH];
    char items[MAX_ITEMS][MAX_NAME_LENGTH];
    float prices[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount;
} Bill;

// Function to calculate total bill
float calculateTotal(float prices[], int quantities[], int size) {
    float total = 0;
    for (int i = 0; i < size; i++) {
        total += prices[i] * quantities[i];
    }
    return total;
}

// Function to save the bill as a text file
void saveBillAsTextFile(Bill bill) {
    char filename[MAX_NAME_LENGTH];
    snprintf(filename, sizeof(filename), "%s.txt", bill.customerName);
    for (int i = 0; i < strlen(filename); i++) {
        if (filename[i] == ' ') {
            filename[i] = '_';
        }
    }

    // Check if file already exists
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        printf("The bill is already printed previously could not complete the action!\n");
        return;
    }

    // Save the bill to a text file
    file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "=====================\n");
        fprintf(file, "       Student Cafe       \n");
        fprintf(file, "=====================\n");
        fprintf(file, "Customer: %s\n", bill.customerName);
        fprintf(file, "---------------------\n");
        fprintf(file, "Sr No | Item Name         | Quantity | Price \n");
        fprintf(file, "---------------------\n");
        for (int i = 0; i < bill.itemCount; i++) {
            fprintf(file, "%-5d | %-17s | %-8d | %.2f\n", i + 1, bill.items[i], bill.quantities[i], bill.prices[i]);
        }
        float total = calculateTotal(bill.prices, bill.quantities, bill.itemCount);
        fprintf(file, "---------------------\n");
        fprintf(file, "Total: %.2f\n", total);
        fprintf(file, "=====================\n");
        fclose(file);
        printf("Bill saved to %s successfully.\n", filename);
    } else {
        printf("Error saving the bill.\n");
    }
}

// Function to create a new bill
void createBill() {
    Bill bill;
    printf("Enter customer name: ");
    scanf(" %[^\n]s", bill.customerName); // This reads the full name including spaces
    printf("Enter number of items: ");
    scanf("%d", &bill.itemCount);

    for (int i = 0; i < bill.itemCount; i++) {
        printf("Enter item %d name: ", i + 1);
        scanf(" %[^\n]s", bill.items[i]); // This reads the full item name including spaces
        printf("Enter item %d price: ", i + 1);
        scanf("%f", &bill.prices[i]);
        printf("Enter item %d quantity: ", i + 1);
        scanf("%d", &bill.quantities[i]);
    }

    float total = calculateTotal(bill.prices, bill.quantities, bill.itemCount);
    printf("\n--- BILL ---\n");
    printf("Customer: %s\n", bill.customerName);
    printf("---------------------\n");
    printf("Sr No | Item Name         | Quantity | Price \n");
    printf("---------------------\n");
    for (int i = 0; i < bill.itemCount; i++) {
        printf("%-5d | %-17s | %-8d | %.2f\n", i + 1, bill.items[i], bill.quantities[i], bill.prices[i]);
    }
    printf("---------------------\n");
    printf("Total: %.2f\n", total);
    printf("=====================\n");

    // Save the bill to a common file
    FILE *file = fopen("bills.txt", "a");
    if (file != NULL) {
        fwrite(&bill, sizeof(Bill), 1, file);
        fclose(file);
        printf("Bill saved successfully.\n");
    } else {
        printf("Error saving the bill.\n");
    }

    // Ask user if they wish to print the bill
    char choice;
    printf("Do you wish to print the bill? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        saveBillAsTextFile(bill);
    }
}

// Function to view all bills
void viewBills() {
    Bill bill;
    FILE *file = fopen("bills.txt", "r");
    if (file != NULL) {
        printf("\n--- ALL BILLS ---\n");
        while (fread(&bill, sizeof(Bill), 1, file)) {
            printf("\nCustomer: %s\n", bill.customerName);
            printf("---------------------\n");
            printf("Sr No | Item Name         | Quantity | Price \n");
            printf("---------------------\n");
            for (int i = 0; i < bill.itemCount; i++) {
                printf("%-5d | %-17s | %-8d | %.2f\n", i + 1, bill.items[i], bill.quantities[i], bill.prices[i]);
            }
            float total = calculateTotal(bill.prices, bill.quantities, bill.itemCount);
            printf("---------------------\n");
            printf("Total: %.2f\n", total);
            printf("=====================\n");
        }
        fclose(file);
    } else {
        printf("No bills found.\n");
    }
}

// Function to search for a bill by customer name
void searchBill() {
    char searchName[MAX_NAME_LENGTH];
    printf("Enter customer name to search: ");
    scanf(" %[^\n]s", searchName);

    Bill bill;
    FILE *file = fopen("bills.txt", "r");
    if (file != NULL) {
        int found = 0;
        while (fread(&bill, sizeof(Bill), 1, file)) {
            if (strcmp(bill.customerName, searchName) == 0) {
                printf("\nCustomer: %s\n", bill.customerName);
                printf("----------------------------------\n");
                printf("Sr No | Item Name                    | Quantity | Price \n");
                printf("----------------------------------\n");
                for (int i = 0; i < bill.itemCount; i++) {
                    printf("%-5d | %-17s | %-8d | %.2f\n", i + 1, bill.items[i], bill.quantities[i], bill.prices[i]);
                }
                float total = calculateTotal(bill.prices, bill.quantities, bill.itemCount);
                printf("----------------------------------\n");
                printf("Total: %.2f\n", total);
                printf("==================================\n");
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Bill not found.\n");
        }
        fclose(file);
    } else {
        printf("No bills found.\n");
    }
}

// Function to print a bill by customer name
void printBill() {
    char searchName[MAX_NAME_LENGTH];
    printf("Enter customer name to search for bill to print: ");
    scanf(" %[^\n]s", searchName);

    Bill bill;
    FILE *file = fopen("bills.txt", "r");
    if (file != NULL) {
        int found = 0;
        while (fread(&bill, sizeof(Bill), 1, file)) {
            if (strcmp(bill.customerName, searchName) == 0) {
                found = 1;
                break;
            }
        }
        fclose(file);

        if (found) {
            printf("Bill found. Do you wish to print the bill? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                saveBillAsTextFile(bill);
            }
        } else {
            printf("Bill not found.\n");
        }
    } else {
        printf("No bills found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- RESTAURANT BILLING SYSTEM ---\n");
        printf("1. Create New Bill\n");
        printf("2. View All Bills\n");
        printf("3. Search Bill by Customer Name\n");
        printf("4. Print Bill by Customer Name\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createBill();
                break;
            case 2:
                viewBills();
                break;
            case 3:
                searchBill();
                break;
            case 4:
                printBill();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
