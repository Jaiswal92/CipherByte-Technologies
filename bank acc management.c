#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS 60
#define MAX_NAME_LENGTH 30

typedef enum {
    SAVINGS,
    CHECKING
} AccountType;

typedef struct {
    int accountNumber;
    char ownerName[MAX_NAME_LENGTH];
    double balance;
    AccountType type;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

int generateAccountNumber() {
    srand(time(NULL));
    return random() % 900000 + 100000;  // 6-digit number
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = generateAccountNumber();

    printf("Enter account holder's name: ");
    scanf(" %[^\n]s", newAccount.ownerName);

    printf("Enter initial balance: ");
    scanf("%lf", &newAccount.balance);

    printf("Enter account type (1 for Savings, 0 for Checking): ");
    int typeChoice;
    scanf("%d", &typeChoice);
    newAccount.type = (typeChoice == 0) ? SAVINGS : CHECKING;

    accounts[accountCount++] = newAccount;
    printf("Account created successfully. Account number: %d\n", newAccount.accountNumber);
}

Account* findAccount(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return &accounts[i];
        }
    }
    return NULL;
}

void deposit() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account* account = findAccount(accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter deposit amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    account->balance += amount;
    printf("Deposit successful. New balance: %.2f\n", account->balance);
}

void withdraw() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account* account = findAccount(accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);

    if (amount <= 0 || amount > account->balance) {
        printf("Invalid amount or insufficient funds.\n");
        return;
    }

    account->balance -= amount;
    printf("Withdrawal successful. New balance: %.2f\n", account->balance);
}

void checkBalance() {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account* account = findAccount(accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Account balance: %.2f\n", account->balance);
}

void calculateInterest() {
    int accountNumber;
    double rate, time;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account* account = findAccount(accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter annual interest rate (%%): ");
    scanf("%lf", &rate);

    printf("Enter time period (in years): ");
    scanf("%lf", &time);

    double interest = account->balance * (rate / 100) * time;
    printf("Estimated interest: %.2f\n", interest);

    if (account->type == SAVINGS) {
        printf("Note: Saving accounts can have compound interest which cannot be calculated here.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nBank Account Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Calculate Interest\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: calculateInterest(); break;
            case 6: printf("Dellighted you visited here.\n"); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}