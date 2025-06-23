#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria) {
    // Sort contacts based on the chosen criteria
    if(sortCriteria>=1 && sortCriteria <= 3){//For validating index
            for(int i=0;i<addressBook->contactCount-1;i++){//Bubble sort logic
                for(int j=0;j<addressBook->contactCount-1-i;j++){
                    int check=0;//stores return value of strcasecmp
                    if(sortCriteria==1)
                        check=strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);//cmp returns +ve if first string is greater else negative
                    else if(sortCriteria==2)
                        check=strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                    else if(sortCriteria==3)
                        check=strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                    if(check>0){
                        Contact temp;
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=temp;
                    }
                }

            }
            printf("-----------------------------------------------------------------------------------------------\n");
            printf("%-4s %-25s %-15s %-35s\n", "No.", "Name", "Phone Number", "Email");
            printf("-----------------------------------------------------------------------------------------------\n");
            for(int i=0;i<addressBook->contactCount;i++) {
               // if(i==0)
                  //  printf("%-4s %-25s %-15s %-35s\n", "No.", "Name", "Phone Number", "Email");
                printf("%-4d %-25s %-15s %-35s\n", i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);   
            }
            printf("-----------------------------------------------------------------------------------------------\n");
    }
    else
        printf("Enter valid number!");//if we enter invalid index it shows warning 
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook) {
    char duplicate[50],num[11],mail[70];
    // For name
    while (1) {
        printf("Enter name:\n");
        scanf(" %[^\n]", duplicate);
       // getchar();
        if (isvalidname(duplicate))
            break;
        else
            printf("Enter a valid name\n");//if invalid continue this loop
    }

    //For phone number
    while (1) {
        printf("Enter mobile number:\n");
        scanf(" %[^\n]", num);
       // getchar();
        if (isvalidphone(addressBook, num,1,0))//1,0 used for switching certain conditions because this validation is used in search also
            break;
        else
            printf("Enter a valid and unique 10-digit mobile number.\n");//if invalid continue this loop
    }

    //For email
    while (1) {
        printf("Enter mail_id:\n");
        scanf(" %[^\n]", mail);
       // getchar();
        if (isvalidmail(addressBook, mail,1,0))//1,0 used for switching certain conditions because this validation is used in search also
            break;
        else
            printf("Enter a valid and unique email address.\n");
    }
    //Copying the data to the database
    strcpy(addressBook->contacts[addressBook->contactCount].name, duplicate);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, num);
    strcpy(addressBook->contacts[addressBook->contactCount++].email, mail);//Increment the count after adding So point to next index
    printf("Contact added successfully!\n");
}


int searchContact(AddressBook *addressBook, int x) {//x is used to select specific contact....its needed whil edi and delete ow print whole list
    while (1) {
        printf("Based on what you want to search:\n1. Search by name\n2. Search by phone\n3. Search by email\nEnter your choice: ");
        int searchChoice;//index storing
        scanf("%d", &searchChoice);
        getchar();
        //validating index
        if (searchChoice >= 1 && searchChoice <= 3) {
            char duplicate[60];//for storing entered value
            int matchcount = 0;

            //Second while loop executes if enter valid index
            while(1) {
            if (searchChoice==1)
                printf("Enter name:\n");
            else if (searchChoice==2)
                printf("Enter phone number:\n");
            else if (searchChoice==3)
                printf("Enter mail_id:\n");
            scanf(" %[^\n]", duplicate);

            // Validate input based on choice
            if ((searchChoice == 1 && !isvalidname(duplicate)) ||(searchChoice == 2 && !isvalidphone(addressBook,duplicate,0,1)) ||(searchChoice == 3 && !isvalidmail(addressBook,duplicate,0,1)))  {
                printf("Enter a valid input!\n");
                continue;//goto initial stage of while loop
            }
            break; //break from inner while loop if input is valid
        }

            //Finding number of matches for storing in an array(then only we can print like 1,2,3.....)
            for (int i = 0; i < addressBook->contactCount; i++) {
                if ((searchChoice == 1 && strcasestr(addressBook->contacts[i].name, duplicate)) ||(searchChoice == 2 && strcasestr(addressBook->contacts[i].phone, duplicate)) ||(searchChoice == 3 && strcasestr(addressBook->contacts[i].email, duplicate))) {
                    matchcount++;
                }
            }


            if (matchcount == 0) {
                printf("Contact not found!\n");
                return 0;
            }

            int arr[matchcount];//For storing index of matched contacts
            //since matchcount is not zero atleast one contact is there
            printf("Contact found!\n-----------------------------------------------------------------------------------------------\n");
            printf("%-4s %-25s %-15s %-35s\n", "No.", "Name", "Phone Number", "Email");
            printf("-----------------------------------------------------------------------------------------------\n");


            int k = 0;//for incrementing array values
            for (int i = 0; i < addressBook->contactCount; i++) {
                if ((searchChoice == 1 && strcasestr(addressBook->contacts[i].name, duplicate)) ||(searchChoice == 2 && strcasestr(addressBook->contacts[i].phone, duplicate)) ||(searchChoice == 3 && strcasestr(addressBook->contacts[i].email, duplicate))) {
                    arr[k] = i+1;//storing index//i+1 beacause if i is zero op will be wrong....print from 0
                    printf("%-4d %-25s %-15s %-35s\n", k + 1,addressBook->contacts[arr[k] - 1].name,addressBook->contacts[arr[k] - 1].phone,addressBook->contacts[i].email);
                    k++;
                }
            }
            printf("-----------------------------------------------------------------------------------------------\n");

            if (x == 0)//0 means no need of one specific contact(used for search only)
                return 1; // only show result, not select
            else if (x == 1) {
                    if (matchcount == 1) {
                           // int result = arr[0];
                            return arr[0];//only one contact means its stored in arr[0]
                        }
                    int index;
                    while(1) {
                            printf("Enter the index number of contact:\n");
                            scanf("%d",&index);
                            getchar();
                            if(index<1 || index>matchcount) {//validating index
                                printf("Enter valid index number\n");
                                continue;
                            }
                            return arr[index-1];//index starts from 0,we are printing from 1 so subtracting 1 will give actual index
                            //Eg if I select 2 it means the actual value of index is stored in arr[1]
                        }
                    }
        }
    else //if not valid index
        printf("Enter a valid number!\n");
    }//while ends
}


void editContact(AddressBook *addressBook) {
	/* Define the logic for Editcontact */
    int x = searchContact(addressBook,1);//1 is used to get index,search contact returns 
    if(x)//contact found ret=non zero else ret =0;if non zero value, true enters loop
    {
        while(1) {
            printf("What do you want to edit\n1.Name\n2.Phone Number\n3.Mail_id\n");
            int edit;
            scanf("%d",&edit);
            getchar();
           
                    if(edit >=1 && edit <= 3) {//validating index
                            if(edit==1) {
                                char duplicate[30];
                                while(1) {
                                        printf("Enter new name:\n");
                                        scanf(" %[^\n]",duplicate);
                                        if(isvalidname(duplicate)) {

                                            strcpy(addressBook->contacts[x-1].name,duplicate);//des,source//x-1 because if the returned index is 1,it means the actual index is zero
                                            printf("Name edited sucessfully!\nNew name :%s\n",addressBook->contacts[x-1].name); 
                                            break;
                                        }
                                        else
                                            printf("Enter a valid name\n");//if invalid continue this loop
                                }
                                break;
                            }
                            else if(edit==2) {
                                char duplicate[11];
                                while(1) {
                                        printf("Enter new number:\n");
                                        scanf(" %[^\n]",duplicate);
                                        if(isvalidphone(addressBook,duplicate,1,0))
                                        {
                                            strcpy(addressBook->contacts[x-1].phone,duplicate);
                                            printf("Phone number edited sucessfully!\nNew phone number:%s\n",addressBook->contacts[x-1].phone);
                                            break;
                                        }
                                        else
                                            printf("Enter a valid phone number\n");//if invalid continue this loop
                                }
                                break;
                            }
                            else if(edit==3)  {
                                char duplicate[50];
                                while(1) {
                                    printf("Enter new mail_id:\n");
                                    scanf(" %[^\n]",duplicate);
                                    if(isvalidmail(addressBook,duplicate,1,0))  {
                                        strcpy(addressBook->contacts[x-1].email,duplicate);
                                        printf("Email_id edited sucessfully!\nNew Email_id :%s\n",addressBook->contacts[x-1].email);
                                        break;
                                    
                                    }
                                    else
                                            printf("Enter a valid mail_id\n");//if invalid continue this loop
                                }
                                break;
                            
                            }
                        }
                        else
                            printf("Enter a valid number!\n");
                }

            
    }
}

void deleteContact(AddressBook *addressBook) {
	/* Define the logic for deletecontact */
    int a =searchContact(addressBook,1);
    if(a) {
        while(1) {
            
                printf("Do you want to delete this contact?\n1.Yes\n2.No\n");
                int index;
                scanf("%d",&index);
                getchar();
                if(index>=1 && index <=2) {//validating index
                        if(index==1) {
                            for(int i=a-1;i<(addressBook->contactCount)-1;i++)//index_contact-1
                                            addressBook->contacts[i] = addressBook->contacts[i + 1]; 
                            addressBook->contactCount--;//Last contact(index) removed
                            printf("Contact deleted!\n");
                            return;
                        }
                        if(index==2)
                            return;
            }
            else
                printf("Enter a valid number!\n");
        }

    }
   
}
//FOR NAME
int isvalidname(char *ptr)    {  //character pointer//address of duplicate passed here
    int i = 0;  
    while(ptr[i]) {
        if(isalpha(ptr[i]) || ptr[i]==' ')//if both 0 means not alphabet then return 0//isalpha() returns 0 if its not equal
            i++;
        else
            return 0;
    }
    return 1;    
}
//FOR PHONE NUMBER
int isvalidphone(AddressBook *addressBook,char *ptr,int x,int y)   {//x to switch uniquephone y to switch string length
//y=1 for searchcontact x=0 search contact
    if(strlen(ptr)==10||(y&&strlen(ptr)<=10))  {
        int i=0;
        while(ptr[i]) {
            if(isdigit(ptr[i]))
                i++;
            else
                return 0;
        }
        if(x==1) {
            if( uniqphone(addressBook,ptr))
                return 1;
            else
                return 0;
        }
        else 
            return 1;
    }
    else
        return 0;
}

int uniqphone(AddressBook *addressBook,char *ptr) {
    for(int i=0;i<addressBook->contactCount;i++) {
        if(strcmp(addressBook->contacts[i].phone,ptr)==0)//Equal//*******strcmp used*******/
            return 0;//not unique
    }
    return 1;//its unique
}

int isvalidmail(AddressBook *addressBook,char*ptr,int x,int y)//x for switching uniqmail y for switchinf @,.com
{//x=0 for searchcontact y=1 for search contact
    int len = strlen(ptr);
    char *result=strstr(ptr,".com");//Searching for substring
    if (  ((strchr(ptr,'@')  && result && result[4]=='\0' && ptr[0] != '@')||y ) && !strchr(ptr,' ')  )  {//if not found returns NULL
        if(x==1) {
            if(uniqmail(addressBook,ptr))
                return 1;
            else
                return 0;
        }
        else 
            return 1;
    }
    else
        return 0;
}
int uniqmail(AddressBook *addressBook,char *ptr) {
    for(int i=0;i<addressBook->contactCount;i++) {
        if(strcmp(addressBook->contacts[i].email,ptr)==0)//Equal//*******strcmp used*******/
            return 0;
    }
    return 1;

}






