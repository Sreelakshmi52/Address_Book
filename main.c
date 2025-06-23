/*
Name : Sreelakshmi Vinod
Date : 15/4/25
Description : Address Book is a small application written in C language. It keeps track of names and telephone/mobile numbers and
               e-mail addresses. It is a console based application which uses standard I/O for adding and deleting contact names, 
               phone numbers and e-mail addresses, searching names and associated numbers and email addresses, updating numbers and 
               email addresses, and deleting contacts
Sample input: 
                Address Book Menu:
                1. Create contact
                2. Search contact
                3. Edit contact
                4. Delete contact
                5. List all contacts
                6. Exit
                Enter your choice:2

                Based on what you want to search:
                1. Search by name
                2. Search by phone
                3. Search by email
                Enter your choice:1
                Enter name:
                john
Sample output:
Contact found!
No.  Name                      Phone Number    Email
1    John Doe                  1234567890      john@example.com
3    Bob Johnson               1112223333      bob@company.com
*/

#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book//its a fn.call

    do {
        printf("\nAddress Book Menu:\n1. Create contact\n2. Search contact\n3. Edit contact\n4. Delete contact\n");
        printf("5. List all contacts\n6. Exit\nEnter your choice: \n");
        scanf("%d", &choice);
        getchar();

        if(choice>=1&&choice<=6) {

                
                switch (choice) {
                    case 1:
                        createContact(&addressBook);//addressBook is a structure
                        break;
                    case 2:
                        searchContact(&addressBook,0);
                        break;
                    case 3:
                        editContact(&addressBook);
                        break;
                    case 4:
                        deleteContact(&addressBook);
                        break;
                    case 5:
                        printf("Select sort criteria:\n1. Sort by name\n2. Sort by phone\n3. Sort by email\n");
                        int sortChoice;
                        printf("Enter your choice:\n");
                        scanf("%d", &sortChoice);
                        getchar();
                        listContacts(&addressBook, sortChoice);
                        break;
                    case 6:
                        printf("Saving and Exiting...\n");
                        saveContactsToFile(&addressBook);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
        }
        else
            printf("Enter valid number!\n");
    } while (choice != 6);
    
       return 0;
}
