/******************************************************************************
Assignment 3: LAB 02 GROUP 4 
Compiling Instructions: enter 'make' in terminal and program should compile.
On first run of program, enter the username/password:
username: admin
password: Password 
This will allow access into the system to begin adding customised users beyond
the default administrator into the user database. To exit the program please
exit through the system, otherwise the database file will not be saved
correctly for the subsequent run of the program. Note that on first run of 
program the compressed files do not exist so an error message will print, 
however once created by the program on subsequent runs they should load. The 
default adminsitrator is an invalid user after another administrator user
is saved into the database.
******************************************************************************/
#include "system.h"

void printMenu(void);
void checkfiles(void);
/******************************************************************************
MAIN FUNCTION
******************************************************************************/
int main(void)
{
    checkfiles();
    printMenu();
    return 1;
}
/******************************************************************************
Main Function: printMenu() 
* Allows the user to login by calling login()
* Allows the user to exit the system

Inputs:
* an integer (1 for Login and 2 for exiting the system)

Outputs:
* None, just navigates to the function stated in the menu
******************************************************************************/
void printMenu(void)
{
    int choice;
    while (choice != 2) 
    {
        choice = 0;
        printf("\n\nPlease select from the following: \n");
        printf("1. Login\n"
               "2. Exit the system \n");
        printf("Enter choice>");
        scanf("%d", &choice);
        while ((getchar()) != '\n');
        switch(choice)
        {
            case 1:
                decompress_file("products", "compressedProducts");
                decompress_file("newsletter", "compressedNewsletter");
                decompress_file("users", "compressedusers"); 
            
                customer_t currentCustomer;
                if (login(&currentCustomer) == 1) 
                {
                    if (currentCustomer.isAdmin == 1) 
                    {
                        adminMenu(&currentCustomer);
                    } else if (currentCustomer.isAdmin == 0)
                    {
                        customerMenu(&currentCustomer);
                    }
                }
                else printf("Invalid login details\n"); 
                break;
            case 2:
                compress_file("products", "compressedProducts");
                compress_file("newsletter", "compressedNewsletter");
                compress_file("users", "compressedusers");
                exit(1);
            default:
                printf("Invalid choice.\n");
                printMenu();
                break;
        }
        compress_file("products", "compressedProducts");
        compress_file("newsletter", "compressedNewsletter");
        compress_file("users", "compressedusers");
    }
}

void checkfiles(void){
    
    FILE *file;
    file = fopen("products","a");
    fclose(file);
    file = fopen("compressedProducts","ab");
    fclose(file);
    file = fopen("newsletter","a");
    fclose(file);
    file = fopen("compressedNewsletter","ab");
    fclose(file);
    file = fopen("users","a");
    fclose(file);
    file = fopen("compressedusers","ab");
    fclose(file);
}

