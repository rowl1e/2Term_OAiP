#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bmpEdit.h"

void invert (pixel *pixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        pixels[i].red = ~pixels[i].red;
        pixels[i].green = ~pixels[i].green;
        pixels[i].blue = ~pixels[i].blue;
    }
}

void grayscale (pixel *pixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        uint8_t average = (pixels[i].red + pixels[i].green + pixels[i].blue) / 3;
        pixels[i].red = average;
        pixels[i].green = average;
        pixels[i].blue = average;
    }
}

void gammaCorrection(pixel *pixels, int width, int height, float gamma) {
    for (int i = 0; i < width * height; i++) {
        pixels[i].red = (uint8_t)(pow(pixels[i].red / 255.0, gamma) * 255);
        pixels[i].green = (uint8_t)(pow(pixels[i].green / 255.0, gamma) * 255);
        pixels[i].blue = (uint8_t)(pow(pixels[i].blue / 255.0, gamma) * 255);
    }
}

int comparePixels(const void *a, const void *b) {
    pixel *pixela = (pixel *)a;
    pixel *pixelb = (pixel *)b;
    uint8_t ya = 0.299 * pixela->red + 0.587 * pixela->green + 0.114 * pixela->blue;
    uint8_t yb = 0.299 * pixelb->red + 0.587 * pixelb->green + 0.114 * pixelb->blue;
    return ya - yb;
}

void median_filter(pixel *pixels, int width, int height, int filter_size) {
    int radius = filter_size / 2;
    pixel *temp = malloc(width * height * sizeof(pixel));
    pixel *neighbors = malloc(filter_size * filter_size * sizeof(pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int count = 0;
            for (int i = -radius; i <= radius; i++) {
                for (int j = -radius; j <= radius; j++) {
                    int ny = y + i;
                    int nx = x + j;
                    if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                        neighbors[count++] = pixels[ny * width + nx];
                    }
                }
            }
            qsort(neighbors, count, sizeof(pixel), comparePixels);
            temp[y * width + x] = neighbors[count / 2];
        }
    }

    memcpy(pixels, temp, width * height * sizeof(pixel));

    free(temp);
    free(neighbors);
}