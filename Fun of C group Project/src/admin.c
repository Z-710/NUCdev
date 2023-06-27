#include "system.h"

#define MAX_NAME_SIZE 11

/******************************************************************************
Main Function: adminMenu(customer_t *currentCustomer)
* This function prints out the adminMenu & allows the user to access different 
  options given in this menu. 

Inputs:
* An integer relating to choice chosen within the menu

Outputs:
* An integer relating to the choice chosen within the menu
* Returns 0 if there is an unsuccessful exit
* Returns 1 if user deliberately exits the menu (successfully)
******************************************************************************/
int adminMenu(customer_t *currentCustomer){
    while (1) {
        int choice;
        printf("Please select a number from the menu: \n");
        printf("1. List customers\n"
            "2. Add customer\n"
            "3. Remove customer\n"
            "4. Change user details\n"
            "5. List products\n"
            "6. Add a product\n"
            "7. Delete a product\n"
            "8. Assign an SKU to a user\n"
            "9. Delete an SKU from a user\n"
            "10. Create Newsletter\n"
            "11. Go back to the Main Menu\n");
        scanf("%d", &choice);
        while ((getchar()) != '\n');
        switch(choice){
            case 1:
                listCustomersAdmin();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                removeCustomer(currentCustomer);
                break;
            case 4: 
                changeCustomersDetails(currentCustomer);
                break;
            case 5:
                listProducts();                
                break;
            case 6:
                addProducts();
                break;
            case 7:
                removeProducts();
                break;
            case 8:
                addSKU();
                break; 
            case 9:
                removeSKU();
                break; 
            case 10:
                createNewsletter();
                break;
            case 11:
                return 1;
            default: 
                printf("Invalid choice.");
                break;
        } 
    }
    return 0;
}

/******************************************************************************
Admin Function 1: listCustomersAdmin()
* Lists all of the customers in the database 

Inputs:
* None

Outputs:
* Prints all of the users 
******************************************************************************/
void listCustomersAdmin(void) {
    customer_t customers[MAX_COMPANY_SIZE]; 
    int currentCompanySize;
    loadUserDetails(customers, &currentCompanySize);
    if (loadUserDetails(customers, &currentCompanySize) != 1) 
    {
        printf("No users found/file error...\n");
        return;
    }

    if (currentCompanySize == 0) 
    {
        printf("No users found...\n");
        return;
    }
    listCustomers(customers, currentCompanySize);
}

/******************************************************************************
Admin Function 2: addCustomer()
* Adds a new customer to the database (calls createCustomer)

Inputs: (calls the createCustomer function)
* Inputs required to create a customer such as name, phone number, password, 
  admin/not admin access

Outputs:
* createCustomerFunction() returns a customer, it is saved into the database
******************************************************************************/
void addCustomer(void){

    char *name = (char*) malloc(21 * sizeof(char));
    if (getString(name, "Enter name: ", 21) != 1) 
    {
        printf("Memory error...\n");
    }

    char *pnumber = (char*) malloc(11 * sizeof(char));
    if (getString(pnumber, "Enter phone number: ", 11) != 1) 
    {
        printf("Memory error...\n");
    }

    char *password = (char*) malloc(21 * sizeof(char));
    if (getString(password, "Enter password: ", 21) != 1) 
    {
        printf("Memory error...\n");
    }

    int admin;
    printf("Is this user an admin? Enter 1 for yes or 0 for no>");
    scanf("%d", &admin);
    getchar();
    while(!(admin == 1 || admin == 0))
    {
        printf("Incorrect input. \n");
        printf("Is this user an admin? Enter 1 for yes or 0 for no>");
        scanf("%d", &admin);
        getchar();
    }

    address_t *address = malloc(sizeof(address_t));
    getAddress(address);
    
    customer_t customer = createCustomer(password, name, pnumber, 
                          *address, admin);

    int currentCompanySize = 0;
    customer_t *customers = (customer_t*) malloc(MAX_COMPANY_SIZE * 
                             sizeof(customer_t));

    loadUserDetails(customers, &currentCompanySize);
    if (currentCompanySize== MAX_COMPANY_SIZE)
    {
        printf("error - maximum company size reached\n");
        return;
    }
    customers[currentCompanySize] = customer;
    printf("\n");
    saveData(customers, ++currentCompanySize);

    /* Free dynamically allocated memory */
    free(name);
    free(pnumber);
    free(password);
    free(customers);
}

/******************************************************************************
Admin Function 3: removeCustomer(customer_t *currentCustomer)
* Removes the selected customer from the database

Inputs: 
* User details

Outputs:
- Deletes the user if it exists, if -1 is selected, the function exits
******************************************************************************/
void removeCustomer (customer_t *currentCustomer) {
    
    customer_t customers[MAX_COMPANY_SIZE];
    int currentCompanySize = 0;

    if (loadUserDetails(customers, &currentCompanySize) != 1) 
    {
        printf("File error\n");
    }
    if (currentCompanySize == 0) 
    {
        printf("No users to delete\n");
        return;
    }
    int run = 1;
    
    while (run) 
    {
        listCustomersNumbered(customers, currentCompanySize);
        printf("Which customer would you like to delete? (1-%d)\n"
                "(-1 to exit)\n", currentCompanySize);
        int input;
        scanf("%d", &input);
        getchar();
        if (input == -1)
        {
            return;
        } else if (input == 0 || input < -1 || input > currentCompanySize)
        {
            printf("invalid input");
            break;
        } else {
            if (cAreEqual(customers[input-1], *currentCustomer) == 1) 
            {
                printf("Cannot delete current user...\n");
            } else {
                if (input== currentCompanySize)
                {
                    saveData(customers, currentCompanySize-1);
                }
                else{
                    while(input<currentCompanySize)
                    {
                        customers[input-1] = customers[input];
                        input++;
                    }
                saveData(customers, input-1);
                    }       
                
                   }
               }
               run = 0;
    }
}
/******************************************************************************
Admin Function 4: changeCustomersDetails(customer_t *currentCustomer)
* Allows admin to change the details for the selected customer

Inputs:
--Part 1--
* 0 to exit changeCustomersDetails()
* 1 to select a user to delete
--Part 2-- (if 1 is selected)
* changeCustomerDetails(selectedCustomer) 
    * we will be brought to the menu of this function to pick which field we want
      to change

Outputs:
* None, just saves the new data
******************************************************************************/
void changeCustomersDetails(customer_t *currentCustomer) {
    printf("What account would you like to change the details of?\n");
    customer_t *customers = malloc(MAX_COMPANY_SIZE * sizeof(customer_t));
    int currentCompanySize = 0;
    loadUserDetails(customers, &currentCompanySize);
    if (currentCompanySize == 0) 
    {
        printf("No users found.\n");
        return;
    }
    int run = 1;
    while (run) 
    {
        listCustomersNumbered(customers, currentCompanySize);
        printf("Select a user (1 - %d | Exit = 0)>", currentCompanySize);
        int *input = malloc(sizeof(int));
        scanf("%d", input);
        getchar();
        if (*input > 0 && *input <= currentCompanySize) 
        {
            customer_t *selectedCustomer = &customers[*input-1];
            while (changeCustomerDetails(selectedCustomer));
            customers[*input-1] = *selectedCustomer;
        } else if (*input == 0) 
        {
            run = 0;
        } else 
        {
            printf("Invalid input, please try again.\n");
        }
    }
    saveData(customers, currentCompanySize);
}
/******************************************************************************
Admin Function 6: addProducts()
*  Allows the admin to add new products to the products file

Inputs: 
* Product Information: SKU, product name, quantity & price

Outputs:
* None, prints all of the products
******************************************************************************/
void addProducts(void){
    char *SKU = (char*) malloc(21 * sizeof(char));
    if (getString(SKU, "Enter SKU: ", 21) != 1) 
    {
        printf("Memory error...\n");
    }
    char *name = (char*) malloc(21 * sizeof(char));
    if (getString(name, "Enter product name: ", 21) != 1) 
    {
        printf("Memory error...\n");
    }
    int quantity = 0;
    printf("Enter quantity: ");
    scanf("%d" , &quantity);
    while(getchar() != '\n');
    while(quantity == 0)
    {
        printf("Memory error...\n Enter quantity: ");
        scanf("%d" , &quantity);
        while(getchar() != '\n');
    }
    float price = 0;
    printf("Enter price: ");
    scanf("%f" , &price);
    while(getchar() != '\n');
    while(price == 0)
    {
        printf("Memory error...\n Enter price: ");
        scanf("%f" , &price);
        while(getchar() != '\n');
    }
  
    product_t product = createProduct(SKU, name, quantity, price);
    product_t *products = (product_t*) malloc(MAX_PRODUCT_SIZE * 
                                            sizeof(product_t));
    int currentProductSize;
    loadProductDetails(products, &currentProductSize); 
    products[currentProductSize] = product;
    currentProductSize += 1;
    saveProductData(products, currentProductSize); 
  
    listProducts();
    printf("\n");
    /* Free dynamically allocated memory */
    free(SKU);
    free(name);
    free(products);   
}
/******************************************************************************
Admin Function 7: removeProducts()
*  Allows the admin to remove selected products from the products file

Inputs:
* Product to be deleted (int)

Outputs:
* None, selected product is just deleted after this function is run
******************************************************************************/
void removeProducts(void){
   
    product_t products[MAX_PRODUCT_SIZE];
    int currentProductSize = 0;
    if(loadProductDetails(products, &currentProductSize) == 0)
    {
        printf("The product list is empty.");
    }
    if (currentProductSize == 0) 
    {
        printf("No products to delete\n");
        return;
    }
    int run = 1;
    
    while (run) 
    {
        listProductsNumbered(products, currentProductSize);
        printf("Which product would you like to delete? (1-%d)\n"
                "(0 to exit)\n", currentProductSize);
        int input = -1;
        scanf("%d", &input);
        getchar();
        if (input == 0) 
        {
            return;
        } else if (input < -1 || input > currentProductSize) 
        {
            printf("Invalid input\n");
            break;
        } else if (input > 0 && input <= currentProductSize) 
        {
            products[input-1] = products[--currentProductSize - 1];
            saveProductData(products, currentProductSize);
            run = 0;
        } else 
        {
            printf("Invalid input\n");
        }
    }
}
/******************************************************************************
Admin Function 8: addSKU()
* Assigns an SKU to the customer

Inputs:
* Customer, SKU to add

Outputs:
* none
******************************************************************************/
void addSKU()
{
    printf("What account would you like to add an SKU to?\n");
    customer_t *customers = malloc(MAX_COMPANY_SIZE * sizeof(customer_t));
    int currentCompanySize = 0;
    loadUserDetails(customers, &currentCompanySize);
    if (currentCompanySize == 0) 
    {
        printf("No users found.\n");
        return;
    }
    int run = 1;
    while (run) 
    {
        listCustomersNumbered(customers, currentCompanySize);
        printf("Select a user (1 - %d | Exit = -1)>", currentCompanySize);
        int *input = malloc(sizeof(int));
        scanf("%d", input);
        getchar();
        if (*input > 0 && *input <= currentCompanySize) 
        {
            customer_t *selectedCustomer = &customers[*input-1];
            int *inputsku = malloc(sizeof(int));
            printf("Input SKU of product:");
            scanf("%d", inputsku);
            int i;
            for (i = 0; i < MAX_PRODUCT_SIZE; i++) 
            {
                if (selectedCustomer->products[i] == 0) 
                {
                    break;
                }
            }
            if (i < MAX_PRODUCT_SIZE) 
            {
                selectedCustomer->products[i] = *inputsku;
            }
        } else if (*input == -1) 
        {
            run = 0;
        } else 
        {
            printf("Invalid input, please try again.\n");
        }
    }
    saveData(customers, currentCompanySize);
}
/******************************************************************************
Admin Function 9: removeSKU()
* Remove an SKU that was assigned to a customer

Inputs:
* Customer name, SKU to delete

Outputs:
* None, running this functions just removes an SKU that was assigned to a user
******************************************************************************/
void removeSKU()
{
    printf("What account would you like to remove an SKU from?\n");
    customer_t *customers = malloc(MAX_COMPANY_SIZE * sizeof(customer_t));
    int currentCompanySize = 0;
    loadUserDetails(customers, &currentCompanySize);
    if (currentCompanySize == 0) 
    {
        printf("No users found.\n");
        return;
    }
    int run = 1;
    while (run) 
    {
        listCustomersNumbered(customers, currentCompanySize);
        printf("Select a user (1 - %d | Exit = -1)>", currentCompanySize);
        int *input = malloc(sizeof(int));
        scanf("%d", input);
        getchar();
        if (*input > 0 && *input <= currentCompanySize) 
        {
            customer_t *selectedCustomer = &customers[*input-1];
            printf("Select an SKU to remove>\n");
            int i;
            for(i=0; i < MAX_PRODUCT_SIZE; i++)
            {
                printf("%d- %d\n",i,selectedCustomer->products[i]);
            }
            int *inputsku = malloc(sizeof(int));
            scanf("%d", inputsku);
            for(i=*inputsku; selectedCustomer->products[i] != 0;i++)
            {
                selectedCustomer->products[i] = selectedCustomer->products[i+1];
            }
            selectedCustomer->products[i-1] = 0;
        } else if (*input == -1) 
        {
            run = 0;
        } else 
        {
            printf("Invalid input, please try again.\n");
        }
    }
    saveData(customers, currentCompanySize);
}


/******************************************************************************
Admin Function 10: createNewsletter()
* Creates a newsletter into the newsletter file

Inputs:
* Month (of newsletter), message

Outputs:
* None, the newsletter file just has information created onto it
******************************************************************************/
void createNewsletter(void)
{
    FILE *filep = fopen("newsletter", "w");
    char month[12];
    getString(month, "Enter month> ", 12);
    char message[300];
    getString(message, "Enter text>", 300);
    fprintf(filep, "MONTHLY NEWSLETTER: %s edition\n %s", month, message);
    fclose(filep);
}

