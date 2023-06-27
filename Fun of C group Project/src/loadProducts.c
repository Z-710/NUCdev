#include "system.h"

/******************************************************************************
Supplementary Functions: loadProductsDetails (product_t products[]
                         int *currentProductSize)
* This function decrypts or loads the product array

Inputs:
* product array(with the product struct) with all exisiting products
* size of the product array

Outputs:
* Returns 0 if decryption of file loading failed
* Returns 1 if successful
******************************************************************************/
int loadProductDetails(product_t products[], int *currentProductSize) 
{
    char output[400*MAX_PRODUCT_SIZE+1], fileName[] = "products";
    if (decrypt(output, fileName) != 1) 
    {
        printf("decryption/loading file failed\n");
        return 0;
    }
    *currentProductSize = 0;
    char *token = output;
    while (*currentProductSize < MAX_PRODUCT_SIZE) 
    {
        int quantity;
        char SKU[21], name[21];
        float price;
        int numFields = sscanf(token, "%[^,],%[^,],%d,%2f",
                               SKU, name, &quantity, &price);
        if (numFields < 4) 
        {
            break;
        }
        products[*currentProductSize].quantity = quantity;
        products[*currentProductSize].price = price;
        strcpy(products[*currentProductSize].sku, SKU);
        strcpy(products[*currentProductSize].name, name);
        *currentProductSize += 1;
        token = strchr(token, '\n');
        token++;
        if (!token || token[0]==EOF ) 
        {
            break;
        }
    }
    return 1;
}
/******************************************************************************
Supplementary Functions: saveProductData (product_t *products
                         int *currentProductSize)
* This function saves the product data into the product list

Inputs:


Outputs:
* Encrypts the products
******************************************************************************/
int saveProductData (product_t *products, int currentProductSize) 
{
    int i;
    char *output = malloc(400*MAX_COMPANY_SIZE);
    output[0] = '\0'; 
    for (i = 0; i < currentProductSize; i++) 
    {
        char record[400];
        sprintf(record, "%s,%s,%d,%f", products[i].sku, products[i].name, 
                products[i].quantity, products[i].price);
        strcat(record, "\n");
        strcat(output, record);
    }
    return encrypt(output, "products");
}
/******************************************************************************
Supplementary Functions: listProducts()
* This function prints all of the products currently in the list

Inputs:
* None, when function is called it also calls loadProductDetails() which 
  decrypts the product file (and allows us to print it)

Outputs:
* Prints all of the products that are currently on the list
******************************************************************************/
void listProducts(void) 
{
    product_t productlist[MAX_PRODUCT_SIZE];
    int size = 0;
    loadProductDetails(productlist, &size);
    if (size == 0){
        printf("No current product data.\n");
    } else {
        printf("\n ----SKU---- -------Product Name------- ----Quantity----"
         "----Price----\n");

        while(size > 0)
        {
            printf(" %-20.20s %-10.10s \t%-4.4d \t\t%-8.2f \n", 
            productlist[size-1].sku, productlist[size-1].name, 
            productlist[size-1].quantity, productlist[size-1].price);
            size--;
        }
    }
}
