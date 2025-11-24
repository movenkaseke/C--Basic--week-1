/*
  online_banking_2025-01-59-91.c
  Author: Kaseke Morven
  Student No.: 2025-01-59-91
  Online Banking System (C)
  Features: Registration, Login, Deposit, Withdraw, Transfer,
            Change Password, Display Account Details, File handling
  Compile: gcc online_banking_2025-01-59-91.c -o online_banking
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATAFILE "accounts.dat"
#define NAME_LEN 100
#define ACCNO_LEN 32
#define PASS_LEN 32

typedef struct {
    char name[NAME_LEN];
    char account_number[ACCNO_LEN];
    char password[PASS_LEN];
    double balance;
} Account;

/* Utility prototypes */
void clear_input_buffer(void);
int account_exists(const char *accno);
int find_account_by_accno(const char *accno, Account *out, long *pos);
int add_account(Account *acc);
int update_account_at_pos(long pos, Account *acc);

/* Feature prototypes */
void register_account(void);
int login(char *logged_accno);
void deposit_funds(const char *accno);
void withdraw_funds(const char *accno);
void transfer_funds(const char *accno);
void change_password(const char *accno);
void display_account_details(const char *accno);

/* Input helpers */
void read_line(char *buffer, int length);

int main(void) {
    int choice;
    char logged_accno[ACCNO_LEN] = {0};

    while (1) {
        printf("\n================= ROCKVIEW UNIVERSITY — ONLINE BANKING =================\n");
        printf("1. Register (Create Account)\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (choice == 1) {
            register_account();
        } else if (choice == 2) {
            if (login(logged_accno)) {
                int sub;
                while (1) {
                    printf("\n--- Account Menu (Account: %s) ---\n", logged_accno);
                    printf("1. Deposit\n");
                    printf("2. Withdraw\n");
                    printf("3. Transfer\n");
                    printf("4. Change Password\n");
                    printf("5. Display Account Details\n");
                    printf("6. Logout\n");
                    printf("Choose option: ");
                    if (scanf("%d", &sub) != 1) {
                        printf("Invalid input.\n");
                        clear_input_buffer();
                        continue;
                    }
                    clear_input_buffer();

                    if (sub == 1) deposit_funds(logged_accno);
                    else if (sub == 2) withdraw_funds(logged_accno);
                    else if (sub == 3) transfer_funds(logged_accno);
                    else if (sub == 4) change_password(logged_accno);
                    else if (sub == 5) display_account_details(logged_accno);
                    else if (sub == 6) { printf("Logging out...\n"); break; }
                    else printf("Invalid option.\n");
                }
            }
        } else if (choice == 3) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
    return 0;
}

/* ---------- Implementation ---------- */

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void read_line(char *buffer, int length) {
    if (fgets(buffer, length, stdin) != NULL) {
        size_t ln = strlen(buffer) - 1;
        if (buffer[ln] == '\n') buffer[ln] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

int account_exists(const char *accno) {
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return 0; // file doesn't exist => no accounts yet
    Account a;
    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        if (strcmp(a.account_number, accno) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int add_account(Account *acc) {
    FILE *fp = fopen(DATAFILE, "ab");
    if (!fp) return 0;
    if (fwrite(acc, sizeof(Account), 1, fp) != 1) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}

int find_account_by_accno(const char *accno, Account *out, long *pos) {
    FILE *fp = fopen(DATAFILE, "rb");
    if (!fp) return 0;
    Account a;
    long index = 0;
    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        if (strcmp(a.account_number, accno) == 0) {
            if (out) *out = a;
            if (pos) *pos = index;
            fclose(fp);
            return 1;
        }
        index++;
    }
    fclose(fp);
    return 0;
}

int update_account_at_pos(long pos, Account *acc) {
    FILE *fp = fopen(DATAFILE, "rb+");
    if (!fp) return 0;
    if (fseek(fp, pos * sizeof(Account), SEEK_SET) != 0) { fclose(fp); return 0; }
    if (fwrite(acc, sizeof(Account), 1, fp) != 1) { fclose(fp); return 0; }
    fclose(fp);
    return 1;
}

/* ---------- Features ---------- */

void register_account(void) {
    Account acc;
    printf("\n--- Register New Account ---\n");
    printf("Full name: ");
    read_line(acc.name, NAME_LEN);
    if (strlen(acc.name) == 0) { printf("Name cannot be empty. Registration cancelled.\n"); return; }

    printf("Account number (choose unique): ");
    read_line(acc.account_number, ACCNO_LEN);
    if (strlen(acc.account_number) == 0) { printf("Account number required.\n"); return; }
    if (account_exists(acc.account_number)) { printf("Account number already exists. Choose another.\n"); return; }

    printf("Password (will not be displayed): ");
    read_line(acc.password, PASS_LEN);
    if (strlen(acc.password) < 4) { printf("Password too short (min 4 chars).\n"); return; }

    printf("Initial deposit amount: ");
    double deposit;
    if (scanf("%lf", &deposit) != 1) {
        printf("Invalid amount. Registration cancelled.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if (deposit < 0) { printf("Deposit cannot be negative.\n"); return; }
    acc.balance = deposit;

    if (add_account(&acc)) printf("Account created successfully!\n");
    else printf("Failed to create account (file error).\n");
}

int login(char *logged_accno) {
    char accno[ACCNO_LEN];
    char pass[PASS_LEN];
    printf("\n--- Login ---\n");
    printf("Account number: "); read_line(accno, ACCNO_LEN);
    printf("Password: "); read_line(pass, PASS_LEN);

    Account acc;
    if (!find_account_by_accno(accno, &acc, NULL)) {
        printf("Account not found.\n");
        return 0;
    }
    if (strcmp(acc.password, pass) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }
    strncpy(logged_accno, accno, ACCNO_LEN);
    printf("Login successful. Welcome, %s!\n", acc.name);
    return 1;
}

void deposit_funds(const char *accno) {
    double amt;
    printf("Enter deposit amount: ");
    if (scanf("%lf", &amt) != 1) { printf("Invalid amount.\n"); clear_input_buffer(); return; }
    clear_input_buffer();
    if (amt <= 0) { printf("Amount must be positive.\n"); return; }

    Account acc; long pos;
    if (!find_account_by_accno(accno, &acc, &pos)) { printf("Account not found (internal).\n"); return; }
    acc.balance += amt;
    if (update_account_at_pos(pos, &acc)) printf("Deposit successful. New balance: %.2f\n", acc.balance);
    else printf("Failed to update account.\n");
}

void withdraw_funds(const char *accno) {
    double amt;
    printf("Enter withdrawal amount: ");
    if (scanf("%lf", &amt) != 1) { printf("Invalid amount.\n"); clear_input_buffer(); return; }
    clear_input_buffer();
    if (amt <= 0) { printf("Amount must be positive.\n"); return; }

    Account acc; long pos;
    if (!find_account_by_accno(accno, &acc, &pos)) { printf("Account not found (internal).\n"); return; }
    if (acc.balance < amt) { printf("Insufficient funds. Current balance: %.2f\n", acc.balance); return; }
    acc.balance -= amt;
    if (update_account_at_pos(pos, &acc)) printf("Withdrawal successful. New balance: %.2f\n", acc.balance);
    else printf("Failed to update account.\n");
}

void transfer_funds(const char *accno) {
    char target[ACCNO_LEN];
    double amt;
    printf("Enter target account number: "); read_line(target, ACCNO_LEN);
    if (strcmp(target, accno) == 0) { printf("Cannot transfer to the same account.\n"); return; }
    if (!account_exists(target)) { printf("Target account does not exist.\n"); return; }

    printf("Enter amount to transfer: ");
    if (scanf("%lf", &amt) != 1) { printf("Invalid amount.\n"); clear_input_buffer(); return; }
    clear_input_buffer();
    if (amt <= 0) { printf("Amount must be positive.\n"); return; }

    Account sender; long pos_sender;
    if (!find_account_by_accno(accno, &sender, &pos_sender)) { printf("Your account not found (internal).\n"); return; }
    if (sender.balance < amt) { printf("Insufficient funds. Current balance: %.2f\n", sender.balance); return; }

    Account receiver; long pos_receiver;
    if (!find_account_by_accno(target, &receiver, &pos_receiver)) { printf("Target account read error.\n"); return; }

    sender.balance -= amt;
    receiver.balance += amt;

    if (update_account_at_pos(pos_sender, &sender) && update_account_at_pos(pos_receiver, &receiver)) {
        printf("Transfer successful. Your new balance: %.2f\n", sender.balance);
    } else {
        printf("Transfer failed during update.\n");
    }
}

void change_password(const char *accno) {
    char oldp[PASS_LEN], newp[PASS_LEN], confirm[PASS_LEN];
    printf("Enter current password: "); read_line(oldp, PASS_LEN);
    Account acc; long pos;
    if (!find_account_by_accno(accno, &acc, &pos)) { printf("Account not found.\n"); return; }
    if (strcmp(acc.password, oldp) != 0) { printf("Current password incorrect.\n"); return; }

    printf("Enter new password: "); read_line(newp, PASS_LEN);
    if (strlen(newp) < 4) { printf("New password too short (min 4).\n"); return; }
    printf("Confirm new password: "); read_line(confirm, PASS_LEN);
    if (strcmp(newp, confirm) != 0) { printf("Passwords do not match.\n"); return; }

    strcpy(acc.password, newp);
    if (update_account_at_pos(pos, &acc)) printf("Password changed successfully.\n");
    else printf("Failed to update password.\n");
}

void display_account_details(const char *accno) {
    Account acc;
    if (!find_account_by_accno(accno, &acc, NULL)) { printf("Account not found.\n"); return; }
    printf("\n--- Account Details ---\n");
    printf("Account holder name: %s\n", acc.name);
    printf("Account number: %s\n", acc.account_number);
    printf("Current balance: %.2f\n", acc.balance);
    printf("(Password is not displayed)\n");
}
