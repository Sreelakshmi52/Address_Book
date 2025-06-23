#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50],phone[20],email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook,int);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
//void saveContactsToFile(AddressBook *AddressBook);
//void loadContactsFromFile(AddressBook *addressBook);

//For Add Contact
int isvalidname(char*);
int isvalidphone(AddressBook *addressBook,char*,int,int);
int isvalidmail(AddressBook *addressBook,char*,int,int);

int uniqphone(AddressBook *addressBook,char *);
int uniqmail(AddressBook *addressBook,char *);
//List Contact
void sortContacts(AddressBook *addressBook,int);



#endif
