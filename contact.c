#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
    if(addressBook->contactCount >= MAX_CONTACTS) {
        printf("Error: Maximum Contact limit reached\n");
        return;
    }

    Contact new_contact;

    // 1. Name Check
    printf("Enter Name: ");
    scanf(" %[^\n]", new_contact.name);
    if (findIndex(addressBook, 1, new_contact.name) != -1) {
        printf("Error: Name already exists!\n");
        return; 
    }

    // 2. Phone Check (with your 10-digit requirement)
    printf("Enter Phone Number: ");
    scanf(" %[^\n]", new_contact.phone);
    if (strlen(new_contact.phone) != 10) {
        printf("Error: Phone must be 10 digits!\n");
        return;
    }
    if (findIndex(addressBook, 2, new_contact.phone) != -1) {
        printf("Error: Phone number already exists!\n");
        return;
    }

    // 3. Email Check (with @ and . requirement)
    printf("Enter Email ID: ");
    scanf(" %[^\n]", new_contact.email);
    if (strstr(new_contact.email, "@") == NULL || strstr(new_contact.email, ".") == NULL) {
        printf("Error: Invalid Email format!\n");
        return;
    }
    if (findIndex(addressBook, 3, new_contact.email) != -1) {
        printf("Error: Email already exists!\n");
        return;
    }

    // Save
    addressBook->contacts[addressBook->contactCount] = new_contact;
    addressBook->contactCount++;
    printf("\nContact saved successfully!\n");
}

int findIndex(AddressBook *addressBook, int choice, const char *searchKey)
{
    int foundIndex = -1;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        switch (choice)
        {
            case 1: // Name
                if (strcasecmp(addressBook->contacts[i].name, searchKey) == 0)
                    foundIndex = i;
                break;
            case 2: // Phone
                if (strcmp(addressBook->contacts[i].phone, searchKey) == 0)
                    foundIndex = i;
                break;
            case 3: // Email
                if (strcasecmp(addressBook->contacts[i].email, searchKey) == 0)
                    foundIndex = i;
                break;
        }
        if (foundIndex != -1) break; // Exit loop if found
    }
    return foundIndex;
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    int validInput = 0;
    char searchKey[50];

    // 1. Get the user's search preference
    do {
        printf("\nSearch By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
            validInput = 1;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            while (getchar() != '\n'); // Clear buffer
        }
    } while (!validInput);

    // 2. Get the search string based on choice
    switch (choice) {
        case 1: printf("Enter the Name: "); break;
        case 2: printf("Enter the Phone: "); break;
        case 3: printf("Enter the Email: "); break;
    }
    scanf(" %[^\n]", searchKey);

    // 3. Call the modified findIndex with the inputs
    int foundIndex = findIndex(addressBook, choice, searchKey);
   
    if (foundIndex != -1)
    {
        printf("\nContact Found:\n");
        printf("Name:  %s\n", addressBook->contacts[foundIndex].name);
        printf("Phone: %s\n", addressBook->contacts[foundIndex].phone);
        printf("Email: %s\n", addressBook->contacts[foundIndex].email);
    }
    else
    {
        printf("\nNo contacts found with that detail.\n");
    }

}

void editContact(AddressBook *addressBook)
{
    int choice;
    int validInput = 0;
    char searchKey[50];

    // 1. Get the user's search preference
    do {
        printf("\nSearch By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
            validInput = 1;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            while (getchar() != '\n'); // Clear buffer
        }
    } while (!validInput);

    // 2. Get the search string based on choice
    switch (choice) {
        case 1: printf("Enter the Name: "); break;
        case 2: printf("Enter the Phone: "); break;
        case 3: printf("Enter the Email: "); break;
    }
    scanf(" %[^\n]", searchKey);

    // 3. Call the modified findIndex with the inputs
    int foundIndex = findIndex(addressBook, choice, searchKey);

    if (foundIndex != -1)
    {
       
        printf("\nContact Found:\n");
        printf("Name:  %s\n", addressBook->contacts[foundIndex].name);
        printf("Phone: %s\n", addressBook->contacts[foundIndex].phone);
        printf("Email: %s\n", addressBook->contacts[foundIndex].email);

        
        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        int editOption;
        scanf("%d", &editOption);

        // Perform the update
        switch (editOption)
        {
        case 1:
            printf("Enter new Name: ");
            scanf(" %[^\n]", addressBook->contacts[foundIndex].name);
            break;
        case 2:
            printf("Enter new Phone: ");
            scanf(" %[^\n]", addressBook->contacts[foundIndex].phone);
            break;
        case 3:
            printf("Enter new Email: ");
            scanf(" %[^\n]", addressBook->contacts[foundIndex].email);
            break;
        default:
            printf("Invalid option. No changes made.\n");
            return;
        }

        printf("Contact updated successfully!\n");
    }
    else
    {
        printf("Contact not found.\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    int choice;
    int validInput = 0;
    char searchKey[50];

    // 1. Get the user's search preference
    do {
        printf("\nSearch By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
            validInput = 1;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            while (getchar() != '\n'); // Clear buffer
        }
    } while (!validInput);

    // 2. Get the search string based on choice
    switch (choice) {
        case 1: printf("Enter the Name: "); break;
        case 2: printf("Enter the Phone: "); break;
        case 3: printf("Enter the Email: "); break;
    }
    scanf(" %[^\n]", searchKey);

    // 3. Call the modified findIndex with the inputs
    int foundIndex = findIndex(addressBook, choice, searchKey);
    
	if (foundIndex != -1)
    {
        printf("\nContact Found:\n");
        printf("Name:  %s\n", addressBook->contacts[foundIndex].name);
        printf("Phone: %s\n", addressBook->contacts[foundIndex].phone);
        printf("Email: %s\n", addressBook->contacts[foundIndex].email);
        
        printf("Are you sure you want to delete? \n(1 for Yes / 0 for No): ");
        int confirm;
        scanf("%d", &confirm);

        if (confirm == 1)
        {
            // The Shifting Logic
            
            for (int i = foundIndex; i < addressBook->contactCount - 1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            // Decrease the total count
            addressBook->contactCount--;
            printf("Contact deleted successfully.\n");
        }
        else
        {
            printf("Deletion cancelled.\n");
        }
    }
    else
    {
        printf("Contact not found.\n");
    }
   
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