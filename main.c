#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice, sortChoice;

    AddressBook addressBook;

    addressBook.contactCount = 0;

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Load contacts\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                loadContactsFromFile(&addressBook);
                break;
            case 8:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
    
       return 0;
}
