#include <stdio.h>
#include <stdlib.h>
#include "bmpReadWrite.h"
#include "bmp.h"

int readBMP (char *filename, BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *infoHeader, pixel **pixels) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: can't open file %s\n", filename);
        return 1;
    }

    fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    if ((*fileHeader).type != 0x4D42) {
        printf("Error: file %s is not a BMP file\n", filename);
        fclose(file);
        return 1;
    }

    fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    if (infoHeader->bitCount != 24) {
        printf("Error: only 24-bit BMP files are supported\n");
        fclose(file);
        return 1;
    }

    *pixels = malloc(infoHeader->width * infoHeader->height * sizeof(pixel));
    if (!(*pixels)) {
        fclose(file);
        return 1;
    }
    fread(*pixels, sizeof(pixel), infoHeader->width * infoHeader->height, file);

    fclose(file);
    return 0;
}

void writeBitmap (char *filename, BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *infoHeader, pixel *pixels) {
   FILE* fp = fopen(filename, "wb");
   if (fp == NULL) {
        printf("Error: can't open file\n");
        exit(1);
   }

   fwrite(fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
   fwrite(infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
   fwrite(pixels, sizeof(pixel), infoHeader->width * infoHeader->height, fp);

   fclose(fp);
}