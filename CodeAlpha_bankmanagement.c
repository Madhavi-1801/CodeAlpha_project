#include <stdio.h>
#include <stdlib.h>

struct Bank {
    int accNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    do {
        printf("\n===== BANK MANAGEMENT SYSTEM =====");
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: printf("\nThank you for using the Bank System!\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

void createAccount() {
    struct Bank b;
    FILE *fp = fopen("bank.dat", "ab");

    if (!fp) {
        printf("\nFile cannot be opened!");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &b.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", b.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &b.balance);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

void deposit() {
    struct Bank b;
    int acc, found = 0;
    float amount;
    FILE *fp = fopen("bank.dat", "rb+");

    if (!fp) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accNo == acc) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            b.balance += amount;

            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("\nAmount Deposited Successfully! New Balance: %.2f\n", b.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nAccount Not Found!\n");
}

void withdraw() {
    struct Bank b;
    int acc, found = 0;
    float amount;
    FILE *fp = fopen("bank.dat", "rb+");

    if (!fp) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accNo == acc) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount > b.balance) {
                printf("\nInsufficient Balance! Current Balance: %.2f\n", b.balance);
            } else {
                b.balance -= amount;
                fseek(fp, -sizeof(b), SEEK_CUR);
                fwrite(&b, sizeof(b), 1, fp);
                printf("\nWithdrawal Successful! Remaining Balance: %.2f\n", b.balance);
            }
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nAccount Not Found!\n");
}

void balanceEnquiry() {
    struct Bank b;
    int acc, found = 0;
    FILE *fp = fopen("bank.dat", "rb");

    if (!fp) {
        printf("\nNo accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accNo == acc) {
            printf("\nAccount Number: %d", b.accNo);
            printf("\nName: %s", b.name);
            printf("\nBalance: %.2f\n", b.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nAccount Not Found!\n");
}
