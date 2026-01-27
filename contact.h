#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
int findIndex(AddressBook *addressBook);
void sort_by_name(AddressBook *AddressBook);
void sort_by_number(AddressBook *AddressBook);
void sort_by_email(AddressBook *AddressBook);


#endif
