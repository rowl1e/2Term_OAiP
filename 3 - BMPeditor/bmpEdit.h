#ifndef BMPEDIT_H
#define BMPEDIT_H

#include "bmp.h"

void invert (pixel *pixels, int width, int height);

void grayscale (pixel *pixels, int width, int height);

void gammaCorrection(pixel *pixels, int width, int height, float gamma);

int comparePixels(const void *a, const void *b);
void median_filter(pixel *pixels, int width, int height, int filter_size);

#endif //BMPEDIT_H