
#include "fetch.h"
#include <stdio.h>
#include <stdlib.h>


int fetchData(const char* inputFilePath, readFile_t* readFile) {
    // Open the binary file for reading
    FILE* inputFile = fopen(inputFilePath, "rb");
    if (inputFile != NULL) {
        // Find the size of the file
        fseek(inputFile, 0, SEEK_END);
        size_t fileSize = ftell(inputFile);
        rewind(inputFile);

        // Calculate the number of elements (assuming 4 bytes per element)
        readFile->size = fileSize / sizeof(uint32_t);

        // Allocate memory for the array
        readFile->data = (uint32_t*)malloc(fileSize);
        if (readFile->data == NULL) {
            perror("Memory allocation error");
            fclose(inputFile);
            return 1;
        }

        // Read the data from the file into the array
        size_t elementsRead = fread(readFile->data, sizeof(uint32_t), readFile->size, inputFile);
        if (elementsRead != readFile->size) {
            fprintf(stderr, "Error reading file\n");
            free(readFile->data);
            fclose(inputFile);
            return 1;
        }

        // Close the file
        fclose(inputFile);

        printf("Conversion complete.\n");

        return 0;

    } else {
        printf("Error opening input file\n");
        return 1;
    }
}





//int fetch(const char* inputFilePath, readFile_t* readFile) {
//    // Open the binary file for reading
//    FILE* inputFile = fopen(inputFilePath, "rb");
//    if (inputFile != NULL) {
//        // Find the size of the file
//        fseek(inputFile, 0, SEEK_END);
//        size_t fileSize = ftell(inputFile);
//        rewind(inputFile);
//
//        // Calculate the number of elements (assuming 4 bytes per element)
//        readFile->size = fileSize / sizeof(uint32_t);
//
//        // Allocate memory for the array
//        readFile->data = (uint32_t*)malloc(fileSize);
//        if (readFile->data == NULL) {
//            perror("Memory allocation error");
//            fclose(inputFile);
//            return 1;
//        }
//
//        // Read the data from the file into the array
//        size_t elementsRead = fread(readFile->data, sizeof(uint32_t), readFile->size, inputFile);
//        if (elementsRead != readFile->size) {
//            fprintf(stderr, "Error reading file\n");
//            free(readFile->data);
//            fclose(inputFile);
//            return 1;
//        }
//
//        // Close the file
//        fclose(inputFile);
//
//        printf("Conversion complete.\n");
//
//        return 0;
//
//    } else {
//        printf("Error opening input file\n");
//        return 1;
//    }
//}

