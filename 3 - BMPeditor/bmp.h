#ifndef BMP_H
#define BMP_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t sizeImage;
    uint32_t xPelsPerMeter;
    uint32_t yPelsPerMeter;
    uint32_t colorUsed;
    uint32_t colorImportant;
} BITMAPINFOHEADER;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel;
#pragma pack(pop)

#endif //BMP_H