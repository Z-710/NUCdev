#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_SIZE 5
#define MAX_COMPANY_SIZE 10
#define MAX_NAME_SIZE 11

/******************************************************************************
STRUCTURES USED
* address struct
* customer struct
* product struct
******************************************************************************/
struct address{
    int number;
    char street[20];
    char suburb[20];
    int postcode;
    char state[4];
};
typedef struct address address_t;

struct customer{
    char password[21];
    char companyName[21];
    char phoneNumber[21];
    address_t address;
    int products[MAX_PRODUCT_SIZE];
    int isAdmin;
};
typedef struct customer customer_t;

struct product{
    char sku[50];
    char name[50];
    int quantity;
    float price;
};
typedef struct product product_t;

/*admin.c functions*/
int adminMenu(customer_t *currentCustomer);
void listCustomersAdmin(void);
void addCustomer (void);
void removeCustomer (customer_t *currentCustomer);
void addProducts(void);
void removeProducts(void);
void addSKU(void);
void removeSKU(void);
void createNewsletter(void);
void changeCustomersDetails(customer_t *currentCustomer);

/*compress.c functions*/
void compress_file(const char* input, const char* compressed);
void decompress_file(const char* input, const char* compressed);

/*customer.c functions*/
int customerMenu(customer_t *currentCustomer);
void viewPersonalInformation(customer_t *customer);
int displayNewsletter(void);
int changeDetails(customer_t *currentCustomer);

/*loadUsers.c functions*/
int loadUserDetails(customer_t *customers, int *currentCompanySize);
int saveData(customer_t *customers, int currentCompanySize);
int encrypt(char *output, char fileName[]);
int decrypt(char *output, char fileName[]);

/*loadProducts.c functions*/
void listProducts(void);
int loadProductDetails(product_t products[], int *currentProductSize);
int saveProductData (product_t *products, int currentProductSize);

/*login.c functions*/
int login(customer_t *customer);

/*types.c functions*/
customer_t createCustomer(char password[], char companyName[], 
                          char phoneNumber[], address_t address, int isAdmin);
customer_t createCustomerProducts (char *password, char *companyName, 
                                   char *phoneNumber, address_t address, 
                                   int *products, int isAdmin);
address_t createAddress(int number, char street[], char suburb[], int postcode, 
                        char state[]);
product_t createProduct(char SKU[],char name[],int quantity,float price);
void printCustomer (customer_t customer);
void printProduct (product_t product);
int getString(char *output, char *prompt, int maxLength);
int cAreEqual(customer_t c1, customer_t c2);
void listCustomersNumbered(customer_t *customers, int currentCompanySize);
void listProductsNumbered(product_t *products, int currentProductSize);
void listCustomers(customer_t *customers, int currentCompanySize);
int getAddress (address_t *address);
int changeCustomerDetails (customer_t *customer);

#endif /*SYSTEM_H*/
