#include <stdio.h>
#include <stdlib.h>

struct Account
{
    int accountNo;
    char name[50];
    float balance;
};

/* CREATE - Add Account */
void addAccount()
{
    struct Account a;
    FILE *fp;

    fp = fopen("bank.dat", "ab");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &a.accountNo);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(struct Account), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully!\n");
}

/* READ - Display Accounts */
void displayAccounts()
{
    struct Account a;
    FILE *fp;

    fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo account records found!\n");
        return;
    }

    printf("\n===== BANK ACCOUNT DETAILS =====\n");

    while (fread(&a, sizeof(struct Account), 1, fp))
    {
        printf("\nAccount Number : %d", a.accountNo);
        printf("\nAccount Holder : %s", a.name);
        printf("\nBalance        : %.2f\n", a.balance);
    }

    fclose(fp);
}

/* UPDATE - Update Account */
void updateAccount()
{
    struct Account a;
    FILE *fp;
    int accountNo;
    int found = 0;

    fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nNo account records found!\n");
        return;
    }

    printf("\nEnter Account Number to update: ");
    scanf("%d", &accountNo);

    while (fread(&a, sizeof(struct Account), 1, fp))
    {
        if (a.accountNo == accountNo)
        {
            printf("\nEnter New Account Holder Name: ");
            scanf(" %[^\n]", a.name);

            printf("Enter New Balance: ");
            scanf("%f", &a.balance);

            fseek(fp, -sizeof(struct Account), SEEK_CUR);

            fwrite(&a, sizeof(struct Account), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
    {
        printf("\nAccount updated successfully!\n");
    }
    else
    {
        printf("\nAccount not found!\n");
    }
}

/* DELETE - Delete Account */
void deleteAccount()
{
    struct Account a;
    FILE *fp;
    FILE *temp;
    int accountNo;
    int found = 0;

    fp = fopen("bank.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Account Number to delete: ");
    scanf("%d", &accountNo);

    while (fread(&a, sizeof(struct Account), 1, fp))
    {
        if (a.accountNo == accountNo)
        {
            found = 1;
        }
        else
        {
            fwrite(&a, sizeof(struct Account), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found)
    {
        printf("\nAccount deleted successfully!\n");
    }
    else
    {
        printf("\nAccount not found!\n");
    }
}

/* MAIN FUNCTION */
int main()
{
    int choice;

    while (1)
    {
        printf("\n\n===== BANK MANAGEMENT SYSTEM =====");
        printf("\n1. Create Account");
        printf("\n2. Display Accounts");
        printf("\n3. Update Account");
        printf("\n4. Delete Account");
        printf("\n5. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                updateAccount();
                break;

            case 4:
                deleteAccount();
                break;

            case 5:
                printf("\nThank you for using Bank Management System!\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
