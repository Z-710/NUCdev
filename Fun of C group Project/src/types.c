#include "system.h"

/******************************************************************************
Supplementary Functions: createCustomer(char *password, char *companyName,
                         char *phoneNumber, address_t address, int isAdmin)
* This function creates a new customer_t from inputs

Inputs: 
* Password, company name, phone number, address (with struct types) and isAdmin

Outputs:
* Returns the customer that was just created
******************************************************************************/
customer_t createCustomer (char *password, char *companyName, char *phoneNumber,
                             address_t address, int isAdmin) 
{
    customer_t customer;

    strcpy(customer.password, password);
    strcpy(customer.companyName, companyName);
    strcpy(customer.phoneNumber, phoneNumber);
    customer.address = address;
    int i;
    for (i = 0; i < MAX_PRODUCT_SIZE; i++) 
    {
        customer.products[i] = 0;
    }
    customer.isAdmin = isAdmin;

    return customer;
}

/******************************************************************************
Supplementary Functions: createAddress(int number, char street[], char suburb[],
                         int postcode, char state[])
* This function creates a new address_t from inputs

Inputs:
* Address number, street, suburb, postcode, state

Outputs:
* Returns the new address that was just created
******************************************************************************/
address_t createAddress (int number, char street[], char suburb[], 
                         int postcode, char state[]) 
{
    address_t address;
    address.number = number;
    strcpy(address.street, street);
    strcpy(address.suburb, suburb);
    address.postcode = postcode;
    strcpy(address.state, state);

    return address;
}

/******************************************************************************
Supplementary Functions: createProduct(char SKU[], char name[], int quantity
                         float price)
* This function creates a new product_t from inputs

Inputs:
* SKU, name, quantity, price

Outputs:
* Returns the new product that was just created
******************************************************************************/
product_t createProduct(char SKU[],char name[],int quantity,float price)
{
    product_t product;
    strcpy(product.sku, SKU);
    strcpy(product.name, name);
    product.quantity = quantity;
    product.price = price;

    return product;
}

/******************************************************************************
Supplementary Functions: printCustomer(customer_t customer)
* This function prints the customer

Inputs:
* None, function is just called

Outputs:
* Prints the customer
******************************************************************************/
void printCustomer(customer_t customer) 
{
    printf("%-20.20s %-10.10s %-4.4d %-10.10s %-10.10s %-4.4d %-3.3s %-20.20s",
        customer.companyName, customer.phoneNumber, 
        customer.address.number, customer.address.street, 
        customer.address.suburb, customer.address.postcode, 
        customer.address.state, customer.password);
}

/******************************************************************************
Supplementary Functions: getString(char *output, char *prompt, int maxLength)
* This function is used to get the string

Inputs:
* Input (based on the prompt)

Outputs:
* Returns 0 if unsuccessful
* Returns 1 if successful
******************************************************************************/
int getString(char *output, char *prompt, int maxLength) 
{
    /*Allocate memory for input buffer*/
    char *input = malloc((maxLength) * sizeof(char));
    if (input == NULL) 
    {
        printf("Error: failed to allocate memory.\n");
        return 0;
    }
    printf("%s", prompt);

    scanf("%[^\n]", input);
    /*clear buffer*/
    while (getchar() != '\n');
    /*size string*/
    input[strcspn(input, "\n")] = '\0';
    int len = strlen(input);
    while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t' || 
                        input[len - 1] == '\n')) {
        input[--len] = '\0';
    }

    /*Copy input to output, up to maxLength characters*/
    strncpy(output, input, maxLength);
    output[maxLength] = '\0';

    /*Free memory for input buffer*/
    free(input);

    return 1;
}

/******************************************************************************
Supplementary Functions: cAreEqual(customer_t c1, customer_t c2)
* This function checks if two customers are equal

Inputs: 
* None, information is entered in a different function

Outputs:
* Returns 0 if customer 1 and customer 2 are not equal
* Returns 1 if customer 1 and customer 2 are equal
******************************************************************************/
int cAreEqual(customer_t c1, customer_t c2) 
{
    if (strcmp(c1.companyName, c2.companyName) == 0 && 
    strcmp(c1.password, c2.password) == 0 &&
    strcmp(c1.phoneNumber, c2.phoneNumber) == 0)
    {
        return 1;
    }
    return 0;
}
/******************************************************************************
Supplementary Functions: printProduct(product_t product)
* This function prints the selected product

Inputs: 
* None, function is just called

Outputs:
* Prints the product information of the selected product
******************************************************************************/
void printProduct(product_t product) 
{
    printf(" %-20.20s %-10.10s \t%-4.4d \t\t%-8.2f \n", 
    product.sku, 
    product.name, 
    product.quantity, 
    product.price);
}

/******************************************************************************
Supplementary Functions: listCustomersNumbered(customer_t *customers, 
                         int currentCompanySize)
* This function prints the list of customers in numbered order

Inputs:
* None, the function is just called

Outputs:
* Returns null if there are no customers
* Otherwise it prints the customers in numbered order
******************************************************************************/
void listCustomersNumbered(customer_t *customers, int currentCompanySize) 
{
    if (currentCompanySize <= 0) 
    {
        printf("No users found\n");
        return;
    }
    int i;
    printf("#- --------Name-------- --Phone--- -------------Address------------"
          "--- ------Password------\n");
    for (i = 0; i < currentCompanySize; i++) 
    {
        printf("%d. ", i+1);
        printCustomer(customers[i]);
        printf("\n");
    }
}
/******************************************************************************
Supplementary Functions: listProductsNumbered(product_t *products,
                         int currentProductSize)
* This function prints the list of products in numbered order

Inputs: 
* None, the function is just called

Outputs:
* Returns null if there are no products
* Otherwise it prints the products in numbered order
******************************************************************************/
void listProductsNumbered(product_t *products, int currentProductSize) 
{
    if (currentProductSize <= 0) 
    {
        printf("No products found\n");
        return;
    }
    int i;
    printf("#- ----SKU---- -------Product Name------- ----Quantity----" 
           "----Price----\n");
    for (i = 0; i < currentProductSize; i++) 
    {
        printf("%d. ", i + 1);
        printProduct(products[i]);
        printf("\n");
    }
}

/******************************************************************************
Supplementary Functions: listCustomers(customer_t *customers,
                         int currentCompanySize)
* This function lists customers

Inputs:
* None, function is just called

Outputs:
* Prints the customers
******************************************************************************/
void listCustomers(customer_t *customers, int currentCompanySize) 
{
    if (currentCompanySize <= 0) 
    {
        printf("No users found\n");
        return;
    }
    int i;
    printf("--------Name-------- --Phone--- --------------Address--------------" 
           "------Password------\n");
    for (i = 0; i < currentCompanySize; i++) 
    {
        printCustomer(customers[i]);
        printf("\n");
    }
}
/******************************************************************************
Supplementary Functions: getAddress(address_t *address)
* This function gets the address

Inputs: 
* Address information

Outputs:
* Returns 0 if unsuccessful
* Returns 1 if successful
******************************************************************************/
int getAddress (address_t *address) 
{
    /*collecting address*/
    int snumber;
    printf("Enter address: number>");
    scanf("%d", &snumber);
    getchar();

    char *street = (char*) malloc(20 * sizeof(char));
    if (getString(street, "Enter address: street: ", 20) != 1) 
    {
        printf("Memory error...\n");
        return 0;
    }

    char *suburb = (char*) malloc(20 * sizeof(char));
    if (getString(suburb, "Enter address: suburb: ", 20) != 1) 
    {
        printf("Memory error...\n");
        return 0;
    }

    int postcode;
    printf("Enter address: postcode>");
    scanf("%d", &postcode);
    getchar();

    char *state = (char*) malloc(4 * sizeof(char));
    if (getString(state, "Enter address: state: ", 4) != 1) 
    {
        printf("Memory error...\n");
        return 0;
    } 

    *address = createAddress(snumber, street, suburb, postcode, state);
    free(street);
    free(suburb);
    free(state);
    return 1;
}

/******************************************************************************
Supplementary Functions: changeCustomerDetails(customer_t *customers)
* This function allows changing the customer information

Inputs:
* Int to navigate through which field to change (switch-case menu)
* String/Int depending on whcih field is to be changed 

Outputs:
* Returns 1 if change is successful
* Returns 0 if change is unsuccessful
******************************************************************************/
int changeCustomerDetails(customer_t *customer)
{
    printf("\n\nWhat details would you like to change?\n");
    printf("--------Name-------- --Phone--- --------------Address--------------"
           "------Password------\n");
    printCustomer(*customer);
    printf("\nName (1) | Phone (2) | Address (3) | Password (4) | Exit (5)\n"
           "Enter choice>");

    int *input = malloc(sizeof(int));
    scanf("%d", input);
    getchar();
    
    switch(*input)
    {
        case 1:
            char *newName = malloc(21 * sizeof(char));
            getString(newName, "Enter new name>", 21);
            strcpy(customer->companyName, newName);
            free(newName);
            return 1;
        case 2:
            char *newPhoneNumber = malloc(11 * sizeof(char));
            getString(newPhoneNumber, "Enter new phone number>", 11);
            strcpy(customer->phoneNumber, newPhoneNumber);
            free(newPhoneNumber);
            return 1;
        case 3:
            printf("Enter new address details:\n");
            address_t *newAddress = malloc(sizeof(address_t));
            if (getAddress(newAddress) == 0) 
            {
                printf("Error getting address.\n");
                return 1;
            }
            customer->address = *newAddress;
            return 1;
        case 4:
            char *newPassword = malloc(21 * sizeof(char));
            getString(newPassword, "Enter new password>", 21);
            strcpy(customer->password, newPassword);
            free(newPassword);
            return 1;
        default:
            return 0;
    }
}
