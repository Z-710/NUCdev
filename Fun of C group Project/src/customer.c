#include "system.h"

/*****************************************************************************
Main Function: customerMenu(customer_t *currentCustomer)
* Allows the customer to choose what they want to do from their menu

Inputs:
* An integer relating to choice chosen within the menu

Outputs:
* An integer relating to the choice chosen within the menu
* Returns 0 if there is an unsuccessful exit
* Returns 1 if user deliberately exits the menu (successfully)
******************************************************************************/
int customerMenu(customer_t *currentCustomer){
    while(1) {
        int choice;
        printf("Please select a number from the menu: \n");
        printf("1. View personal information \n"
           "2. Change details\n"
           "3. Browse current products \n"
           "4. Read this month's newsletter \n"
           "5. Go back to the Main Menu \n");
        scanf("%d", &choice);
        while ((getchar()) != '\n');
        switch(choice){
            case 1:
                viewPersonalInformation(currentCustomer);
                break;
            case 2:
                changeDetails(currentCustomer);
                break;
            case 3:
                listProducts(); /*called in loadProducts.c */
                break;
            case 4:
                displayNewsletter();
                break;
            case 5: 
                return 1;
            default: 
                printf("Invalid choice.");
                break;
        }
    }
    return 0;
}

/*****************************************************************************
Customer Function 1: viewPersonalInformation()
* Allows the customer to view their own information

Inputs: 
* None, function is called through the customerMenu()

Outputs:
* Prints the customer information, otherwise returns nothing (void)
******************************************************************************/
void viewPersonalInformation(customer_t *customer){
    printf("Personal Details\n");
    printf("Name> %s\n", customer->companyName);
    printf("Phone Number> %s\n", customer->phoneNumber);
    printf("Address> %i %s %s %i %s\n", customer->address.number, 
          customer->address.street, customer->address.suburb, 
          customer->address.postcode, customer->address.state);
}
/*****************************************************************************
Customer Function 2: changeDetails(customer_t *currentCustomer)
* Allows the customer to change their own information

Inputs: 
* New details for current customer

Outputs:
* Returns 1 
******************************************************************************/
int changeDetails(customer_t *currentCustomer)
{
    customer_t *customers = (customer_t*) malloc(MAX_COMPANY_SIZE * 
                                                 sizeof(customer_t));
    int currentCompanySize = 0;
    loadUserDetails(customers, &currentCompanySize);  
    int i = 0;
    for(i = 0; i< currentCompanySize; i++){
        if(cAreEqual(customers[i],*currentCustomer)){
            customer_t *selectedCustomer = &customers[i];
            while (changeCustomerDetails(selectedCustomer));
            saveData(customers, currentCompanySize);
            *currentCustomer->companyName = 
                *selectedCustomer->companyName;
            *currentCustomer->password = 
                *selectedCustomer->password;
            *currentCustomer->phoneNumber = 
                *selectedCustomer->phoneNumber;
            currentCustomer->address.number = 
                selectedCustomer->address.number;
            *currentCustomer->address.street = 
                *selectedCustomer->address.street;
            *currentCustomer->address.suburb = 
                *selectedCustomer->address.suburb;
            currentCustomer->address.postcode = 
                selectedCustomer->address.postcode;
            *currentCustomer->address.state = 
                *selectedCustomer->address.state;
        }
    } 
    return 1;
}
/*****************************************************************************
Customer Function 3: displayNewsletter()
* Allows the customer to view newsletters if it exists

Inputs:
* None, function is run when it is selected in the customerMenu()

Outputs:
* Returns 1 if a newsletter exists and is printed out
* Returns 0 if no newsletter exists
******************************************************************************/
int displayNewsletter(void)
{
    FILE *filep = fopen("newsletter", "r");
    if (filep == NULL)
    {
        printf("No current newsletter edition to view.\n");
        return 0;
    }
    char i;

    while (i != EOF)
    {
        printf("%c", i);
        i = getc(filep);
    }
    printf("\n");
    fclose(filep);
    return 1;
}
