#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for account details
typedef struct {
    char name[50];
    int accountNumber;
    char password[20];
    double balance;
} Account;

// Function declarations
void registerAccount(Account accounts[], int *count);
void deposit(Account accounts[], int count);
void withdraw(Account accounts[], int count);
void transfer(Account accounts[], int count);
void changePassword(Account accounts[], int count);
void displayAccount(Account accounts[], int count);
int findAccount(Account accounts[], int count, int accNumber);
void saveToFile(Account accounts[], int count);
void loadFromFile(Account accounts[], int *count);

int main() {
    Account accounts[100];
    int accountCount = 0;
    int choice;

    // Load existing accounts from file
    loadFromFile(accounts, &accountCount);

    do {
        printf("\n===== ONLINE BANKING SYSTEM =====\n");
        printf("1. Register Account\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Transfer Funds\n");
        printf("5. Change Password\n");
        printf("6. Display Account Details\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: registerAccount(accounts, &accountCount); break;
            case 2: deposit(accounts, accountCount); break;
            case 3: withdraw(accounts, accountCount); break;
            case 4: transfer(accounts, accountCount); break;
            case 5: changePassword(accounts, accountCount); break;
            case 6: displayAccount(accounts, accountCount); break;
            case 7: saveToFile(accounts, accountCount); printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 7);

    return 0;
}

// Register new account
void registerAccount(Account accounts[], int *count) {
    Account newAcc;
    printf("Enter full name: ");
    scanf(" %[^\n]", newAcc.name); // read full name with spaces
    printf("Enter account number: ");
    scanf("%d", &newAcc.accountNumber);
    printf("Set a password (max 19 chars, no spaces): ");
    scanf("%19s", newAcc.password);
    printf("Enter initial deposit: ");
    scanf("%lf", &newAcc.balance);

    accounts[*count] = newAcc;
    (*count)++;
    printf("Account registered successfully!\n");
}

// Deposit funds
void deposit(Account accounts[], int count) {
    int accNum;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    int idx = findAccount(accounts, count, accNum);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    if(amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    accounts[idx].balance += amount;
    printf("Deposit successful. New balance: %.2lf\n", accounts[idx].balance);
}

// Withdraw funds
void withdraw(Account accounts[], int count) {
    int accNum;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    int idx = findAccount(accounts, count, accNum);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    if(amount <= 0 || amount > accounts[idx].balance) {
        printf("Invalid or insufficient funds!\n");
        return;
    }

    accounts[idx].balance -= amount;
    printf("Withdrawal successful. New balance: %.2lf\n", accounts[idx].balance);
}

// Transfer funds
void transfer(Account accounts[], int count) {
    int fromAcc, toAcc;
    double amount;
    printf("Enter your account number: ");
    scanf("%d", &fromAcc);
    int idxFrom = findAccount(accounts, count, fromAcc);
    if(idxFrom == -1) {
        printf("Sender account not found!\n");
        return;
    }

    printf("Enter recipient account number: ");
    scanf("%d", &toAcc);
    int idxTo = findAccount(accounts, count, toAcc);
    if(idxTo == -1) {
        printf("Recipient account not found!\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    if(amount <= 0 || amount > accounts[idxFrom].balance) {
        printf("Invalid amount or insufficient funds!\n");
        return;
    }

    accounts[idxFrom].balance -= amount;
    accounts[idxTo].balance += amount;
    printf("Transfer successful. Your new balance: %.2lf\n", accounts[idxFrom].balance);
}

// Change password
void changePassword(Account accounts[], int count) {
    int accNum;
    char oldPass[20], newPass[20];
    printf("Enter account number: ");
    scanf("%d", &accNum);
    int idx = findAccount(accounts, count, accNum);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter old password: ");
    scanf("%19s", oldPass);

    if(strcmp(accounts[idx].password, oldPass) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%19s", newPass);
    strcpy(accounts[idx].password, newPass);
    printf("Password changed successfully!\n");
}

// Display account details
void displayAccount(Account accounts[], int count) {
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    int idx = findAccount(accounts, count, accNum);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("\n--- Account Details ---\n");
    printf("Name: %s\n", accounts[idx].name);
    printf("Account Number: %d\n", accounts[idx].accountNumber);
    printf("Balance: %.2lf\n", accounts[idx].balance);
}

// Find account by account number
int findAccount(Account accounts[], int count, int accNumber) {
    for(int i = 0; i < count; i++) {
        if(accounts[i].accountNumber == accNumber)
            return i;
    }
    return -1;
}

// Save accounts to file
void saveToFile(Account accounts[], int count) {
    FILE *fp = fopen("accounts.dat", "wb");
    if(fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(accounts, sizeof(Account), (size_t)count, fp);
    fclose(fp);
}

// Load accounts from file
void loadFromFile(Account accounts[], int *count) {
    FILE *fp = fopen("accounts.dat", "rb");
    if(fp == NULL) {
        *count = 0;
        return;
    }
    *count = (int)fread(accounts, sizeof(Account), 100, fp);
    fclose(fp);
}
