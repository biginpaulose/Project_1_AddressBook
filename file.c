#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    char fileName[50];
    
    // 1. Ask user for the file name
    printf("Enter the filename to save (e.g., phonebook.txt): ");
    scanf(" %[^\n]", fileName); 

    // 2. Open file in "w" (Write) mode. 
    FILE *fp = fopen(fileName, "w");

    if (fp == NULL) 
    {
        printf("Error: Failed to create or open file.\n");
        return;
    }

    // 3. Loop and Save
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        
        fprintf(fp, "%s,%s,%s\n", 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("Saved successfully to %s\n", fileName);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    char fileName[50];
    printf("Enter the filename to load: ");
    scanf(" %[^\n]", fileName); // Read filename with spaces

    FILE *fp = fopen(fileName, "r"); 

    if (fp == NULL) 
    {
        printf("Error: Could not open file '%s'. (File might not exist)\n", fileName);
        return;
    }

    
    // (to APPEND to existing contacts, remove this line)
    addressBook->contactCount = 0;

    // Temporary buffers to hold data while reading
    char name[50], phone[20], email[50];

   
    // Format: Read Name until comma, skip comma, Read Phone until comma, skip comma, Read Email until newline
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", name, phone, email) != EOF) 
    {
        // Safety Check: Don't exceed array limit
        if (addressBook->contactCount >= MAX_CONTACTS) 
        {
            printf("Address Book is full! Stopped loading.\n");
            break;
        }

        // Copy read data into the struct
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);

        addressBook->contactCount++;
    }

    fclose(fp);
    printf("Successfully loaded %d contacts from '%s'.\n", addressBook->contactCount, fileName);
}
