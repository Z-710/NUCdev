#include "system.h"

/******************************************************************************
Main Function: login(customer_t customer) function
* this function allows a user to login by entering their password, which is 
compared to encrypted password in user file.

Inputs:
* username (string)
* password (string)

Outputs:
* Returns 0 if the login information is incorrect
* Returns -1 if login information is correct
******************************************************************************/
int login(customer_t *customer)
{
    int currentCompanySize = 0, adminExists = 0, i;
    customer_t customers[MAX_COMPANY_SIZE];
    int loadSuccess = loadUserDetails(customers, &currentCompanySize);
    if (loadSuccess != 1) 
    {
        printf("No user database found\n");

    }

    for (i = 0; i < currentCompanySize; i++) {
        if (customers[i].isAdmin) adminExists++;
    }

    char *name = malloc(21 * sizeof(char));
    char *pass = malloc(21 * sizeof(char));

    getString(name, "Enter name: ", 21);
    getString(pass, "Enter password: ", 21);
    if (adminExists == 0 &&
        strcmp(name, "admin") == 0 && strcmp(pass, "Password") == 0) {
        address_t *address = malloc(sizeof(address_t));
        *address = createAddress(1, "Pleasant Ave", "Default", 2500, "NSW");
        customer_t *admin = malloc(sizeof(customer_t));
        *admin = createCustomer("Password", "admin", "0412345678", *address, 1);
        admin->isAdmin = 1;
        *customer = *admin;
        free(name);
        free(pass);
        return 1;
    }
    if (loadSuccess == 1) {
        int i;
        for (i = 0; i < currentCompanySize; i++) 
        {
            if (strcmp(name,customers[i].companyName) == 0 && 
                strcmp(pass, customers[i].password) == 0) {
                *customer = customers[i];
                free(name);
                free(pass);
                return 1;
            }
        }
    }
    printf("Login details not found\n");
    free(name);
    free(pass);
    return 0;
}
