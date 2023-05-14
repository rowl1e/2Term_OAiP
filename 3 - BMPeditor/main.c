#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get.h"
#include "bmpReadWrite.h"
#include "bmpEdit.h"

#define MAX_LEN 256

int main () {
    printf("Adobe Photoshop 1990s\n");
    char *inputFilename = malloc(MAX_LEN);
    printf("Enter filename: ");
    inputFilename = get_str();
   
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    pixel *pixels;

    if (readBMP(inputFilename, &fileHeader, &infoHeader, &pixels) == 1) {
        system("pause");
        exit(0);
    }

    int option;
    do {
        printf("\nChoose an option:\n"
               "1. Negative\n"
               "2. Black and white\n"
               "3. Median filter\n"
               "4. Gamma correction\n"
               "5. Save and exit\n");
        option = getintMinMax(1, 5);
        switch (option) {
            case 1:
                invert(pixels, infoHeader.width, infoHeader.height);
                break;
            case 2:
                grayscale(pixels, infoHeader.width, infoHeader.height);
                break;
            case 3:
                printf("Enter filter size:\n");
                int filter_size = getintMin(1);
                median_filter(pixels, infoHeader.width, infoHeader.height, filter_size);
                break;
            case 4:
                printf("Enter gamma value: ");
                float gamma = getfloatMin(0);
                gammaCorrection(pixels, infoHeader.width, infoHeader.height, gamma);
                break;
        }
        if (option != 5) {
            printf("Press ENTER to cointinue...(To save and exit press ESC)\n");
            if (_getch() == 27) {
                break;
            }
        }
    } while (option != 5);

    char *outputFilename = malloc (MAX_LEN);
    printf("\nEnter output filename(.bmp): ");
    outputFilename = get_str();
    if(strlen(outputFilename) == 0) {
        printf("Error: can't open file\n");
        free(pixels);
        system("pause");
        exit(0);
    }
    strcat(outputFilename, ".bmp");

    writeBitmap(outputFilename, &fileHeader, &infoHeader, pixels);

    free(pixels);
    system("pause");
    return 0;
}