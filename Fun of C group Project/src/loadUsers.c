#include "system.h"

/******************************************************************************
Supplementary Functions: loadUserDetails(customer_t *customers,
                         int *currentCompanySize)
* This function loads all users, by loading them from the database file into 
  a customer_t array containing each customer. 

Inputs:
*

Outputs:
* Returns 1 on success
* Returns 0 on fail
******************************************************************************/
int loadUserDetails(customer_t *customers, int *currentCompanySize) 
{
    char *output = malloc(400*MAX_COMPANY_SIZE*sizeof(char)), 
    fileName[] = "users";
    if (decrypt(output, fileName) != 1) 
    {
        printf("decryption/loading file failed\n");
        *currentCompanySize =0;
        return 0;
    }
    *currentCompanySize = 0;
    char *token = output;
    while (*currentCompanySize < MAX_COMPANY_SIZE) 
    {
        int isAdmin, number, postcode, products[MAX_PRODUCT_SIZE];
        char password[21], companyName[21],
             phoneNumber[11], street[20],
             suburb[20], state[4];
        int numFields = sscanf(token, 
            "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^,],%d,%[^,],%d,%d,%d,%d,%d",
            password, companyName, phoneNumber, &isAdmin, &number,street, 
            suburb, &postcode, state, &products[0], &products[1], 
            &products[2], &products[3], &products[4]);

        if (numFields < 9) 
        {
            break;
        }
        customers[*currentCompanySize].isAdmin = isAdmin;
        customers[*currentCompanySize].address.number = number;
        customers[*currentCompanySize].address.postcode = postcode;
        strcpy(customers[*currentCompanySize].password, password);
        strcpy(customers[*currentCompanySize].companyName, companyName);
        strcpy(customers[*currentCompanySize].phoneNumber, phoneNumber);
        strcpy(customers[*currentCompanySize].address.street, street);
        strcpy(customers[*currentCompanySize].address.suburb, suburb);
        strcpy(customers[*currentCompanySize].address.state, state);

        for (int j = 0; j < MAX_PRODUCT_SIZE && j < numFields - 9; j++) 
        {
            customers[*currentCompanySize].products[j] = products[j];
        }

        *currentCompanySize += 1;
        token = strchr(token, '\n');
        if (!token || token[0]== EOF) 
        {
            break;
        }
        token++;
    }
    free(output);
    return 1;
}
/******************************************************************************
Supplementary Functions: saveData(customer_t *customer, int currentCompanySize)
* Formats the list of customers and then encrypts it, saves encrypted list into 
the text file

Inputs:
* None, function is just called

Outputs: 
* Encrypted list of customers
******************************************************************************/
int saveData (customer_t *customer, int currentCompanySize) 
{
    if (currentCompanySize> MAX_COMPANY_SIZE)
    {
        printf("Error Saving Data - exceeded maximum company size");
        return 0;
    }

    int i, j;
    char *output = malloc(400*sizeof(char));
    output[0]= '\0';
    i=0;
    for (i = 0; i < currentCompanySize; i++) 
    {
        j=0;
        char *record = calloc(400, sizeof(char));
        sprintf(record, "%s,%s,%s,%d,%d,%s,%s,%d,%s", customer[i].password, 
        customer[i].companyName, customer[i].phoneNumber, customer[i].isAdmin, 
        customer[i].address.number, customer[i].address.street, 
        customer[i].address.suburb, customer[i].address.postcode, 
        customer[i].address.state);

        for (j = 0; j < MAX_PRODUCT_SIZE; j++) 
        {
            char product_str[10];
            sprintf(product_str, ",%d", customer[i].products[j]);
            strcat(record, product_str);
        }
        strcat(record, "\n");
        if (i!=0)
        {
            output = realloc(output, (strlen(output) + strlen(record) + 1) 
                             * sizeof(char));
        }
        strcat(output, record);
        free(record);
    }
    return encrypt(output, "users");
}
/******************************************************************************
Supplementary Functions: encrypt(char *output, char fileName[])
* The encrypt function is called to by saveData etc in order to execute 
encryption. It encrypts the given string output and writes into the given file

Inputs:
* None, function is just called

Outputs:
* Returns 0 if unsuccessful
* Returns 1 if successful
******************************************************************************/
int encrypt(char *output, char fileName[]) 
{
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    FILE *file;
    file = fopen(fileName, "w");
    if (file == NULL) 
    {
        return 0;
    }
    int i, j;
    for (i = 0; output[i]; i++) 
    {
        j = i % strlen(key);
        output[i] = output[i] + key[j] - 'A';
    }
    fprintf(file, "%s", output);
    fclose(file);
    free(output);
    return 1;
}
/******************************************************************************
Supplementary Functions: decrypt(char *output, char fileName[])
* is called to by loadUserDetails and reverses the encrypt function.

Inputs:
* None, function is just called

Outputs:
* Returns 0 if unsuccessful
* Returns 1 if successful
******************************************************************************/
int decrypt(char *output, char fileName[]) 
{
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) 
    {
        return 0;
    }
    int i, j;
    for (i = 0; i < 400*MAX_COMPANY_SIZE && fscanf(file, "%c", 
         &output[i]) != EOF; i++)
    {
        j = i % strlen(key);
        output[i] = output[i] - key[j] + 'A';
    }
    output[i] = '\0';
    fclose(file);
    return 1;
}
