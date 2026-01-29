#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"



void listContacts(AddressBook *addressBook) 
{
    // 1. Check if there are any contacts to display
    if (addressBook->contactCount == 0)
    {
        printf("\nAddress Book is empty. No contacts to list.\n");
        return;
    }

    int sortChoice;
    int validInput = 0;

    // 2. Loop until we get a valid choice (1, 2, or 3)
    do {
        printf("\nSort By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");

        // Check if scanf successfully read an integer
        if (scanf("%d", &sortChoice) == 1) 
        {
            if (sortChoice >= 1 && sortChoice <= 3) 
            {
                validInput = 1; // Valid input, exit loop
            } 
            else 
            {
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
            }
        } 
        else 
        {
            // Input was not a number (e.g., 'a'), clear the buffer
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
        }

    } while (!validInput);


    // 3. Perform the Sort
    switch (sortChoice) 
    {
        case 1:
            sort_by_name(addressBook);
            break;
        case 2:
            sort_by_number(addressBook);
            break;
        case 3:
            sort_by_email(addressBook);
            break;
    }

    // 4. Print the Table
    printf("\n\t\tNames\t\t\tPhone No\t\tEmail ID\n");
    printf("\t\t==============================================================\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("\t\t%-20s\t%-15s\t%-20s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("\t\t==============================================================\n");
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Maximum Contact limit reached");
        return;
    }

    Contact new_contact;
    printf("Enter Name:");
    scanf(" %[^\n]",new_contact.name);
    printf("Enter Phone Number:");
    scanf(" %[^\n]",new_contact.phone);
    printf("Enter Email ID:");
    scanf(" %[^\n]",new_contact.email);

    addressBook->contacts[addressBook->contactCount] = new_contact;
    addressBook->contactCount++;
    
    printf("\nContact saved successfully!\n");
}

int findIndex(AddressBook *addressBook)
{
    int choice;
    int validInput;
    do {
        printf("\nSearch By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");

        // Check if scanf successfully read an integer
        if (scanf("%d", &choice) == 1) 
        {
            if (choice >= 1 && choice <= 3) 
            {
                validInput = 1; // Valid input, exit loop
            } 
            else 
            {
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
            }
        } 
        else 
        {
            // Input was not a number (e.g., 'a'), clear the buffer
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
        }

    } while (!validInput);



    char searchKey[50];
    int foundIndex = -1; // -1 means haven't found anyone yet

    
    switch (choice)
    {
    case 1:
        printf("Enter the Name: ");
        scanf(" %[^\n]", searchKey);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, searchKey) == 0)
            {
                foundIndex = i;
                break; 
            }
        }
        break;

    case 2:
        printf("Enter the Phone: ");
        scanf(" %[^\n]", searchKey);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, searchKey) == 0)
            {
                foundIndex = i;
                break;
            }
        }
        break;

    case 3:
        printf("Enter the Email: ");
        scanf(" %[^\n]", searchKey);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, searchKey) == 0)
            {
                foundIndex = i;
                break;
            }
        }
        break;
    }
    return foundIndex;
}

// Helper: Sort by Name 
void sort_by_name(AddressBook *addressBook) 
{
    Contact temp;
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) 
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}
// Helper: Sort by Phone
void sort_by_number(AddressBook *addressBook) 
{
    Contact temp;
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            // Compare Phone Numbers
            if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0) 
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

// Helper: Sort by Email
void sort_by_email(AddressBook *addressBook) 
{
    Contact temp;
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            // Compare Emails
            if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0) 
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}