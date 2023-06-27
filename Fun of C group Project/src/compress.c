#include "system.h"

/******************************************************************************
GLOBAL VARIABLES 
******************************************************************************/
const char* input = "products.txt"; 
const char* compressed = "compressed.bin";

/******************************************************************************
Compression Functions: compress_file(const char* input, const char* compressed)
* This function compresses the products.txt file

Inputs: 
* none, but calls products file, a compressed file in the function argument

Outputs:
* Compressed file .bin
******************************************************************************/
void compress_file(const char* input, const char* compressed)
{
    FILE* inputfilep= fopen(input, "rb");
    if (!inputfilep)
    {
        printf("Error: Failed to find database file. \n");
        return;
    }

    FILE* outputfilep = fopen(compressed, "wb");
    if(!outputfilep)
    {
        printf("Error: Failed to open the compressed file.\n");
        fclose(inputfilep);
        return;
    }

    /* Gets the first character of the source file */
    int current, previous;
    int count = 1;
    
    current = fgetc(inputfilep);
    previous = current;

    while(current != EOF)
    {
        current = fgetc(inputfilep);

        /* Count if character is same */
        if(current == previous)
        {
            count++;
        }
        else
        {
            fwrite(&count, sizeof(int), 1, outputfilep);
            fputc(previous, outputfilep);

            count = 1;
            previous = current;
        }
    }

    fputc(previous, outputfilep);

    fclose(inputfilep);
    fclose(outputfilep);

}
/******************************************************************************
Compression Functions: decompress_file(const char* input, const char* compressed)
* This function decompresses the compressed.bin file

Inputs: 
* none, but calls products file, a compressed file in the function argument

Outputs:
* Decompressed products.txt file
******************************************************************************/
void decompress_file(const char* input, const char* compressed)
{
    FILE* outputfilep = fopen(compressed, "rb");
    if(!outputfilep)
    {
        printf("Failed to open the compressed file %s.\n", compressed);
        return;
    }

    FILE* inputfilep = fopen(input, "wb");
    if(!inputfilep)
    {
        printf("Failed to open the database file %s.\n", input);
        fclose(outputfilep);
        return;
    }

    int count, i;
    char characters;
    
    while(fread(&count, sizeof(int), 1, outputfilep) == 1)
    {
        fread(&characters, sizeof(char), 1, outputfilep);
        
        for(i = 0; i < count; ++i)
        {
            fwrite(&characters, sizeof(char), 1, inputfilep);
        }
    }
    fclose(outputfilep);
    fclose(inputfilep);
}
