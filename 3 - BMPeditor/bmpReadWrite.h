#ifndef BMPREADWRITE_H
#define BMPREADWRITE_H

#include "bmp.h"

int readBMP (char *filename, BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *infoHeader, pixel **pixels);
void writeBitmap (char *filename, BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *infoHeader, pixel *pixels);

#endif //BMPREADWRITE_H