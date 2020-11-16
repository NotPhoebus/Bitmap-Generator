#include <iostream>
#include <cstdint>
#include <string>

#include "bitmap_generator.h"

void bitmap(uint8_t* image, uint32_t height, uint32_t width, std::string imageFileName)
{
    uint32_t widthInBytes = width * BYTES_PER_PIXEL;

    uint8_t padding[3] = { 0, 0, 0 };
    uint32_t paddingSize = (4 - (widthInBytes) % 4) % 4;

    uint32_t stride = (widthInBytes)+paddingSize;

    FILE* imageFile = fopen(imageFileName.c_str(), "wb");

    uint8_t* fileHeader = bitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    uint8_t* infoHeader = bitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    uint32_t i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i * widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

uint8_t* bitmapFileHeader(uint32_t height, uint32_t stride)
{
    uint32_t fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static uint8_t fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[0] = (uint8_t)(0x042);
    fileHeader[1] = (uint8_t)(0x04d);
    fileHeader[2] = (uint8_t)(fileSize);
    fileHeader[3] = (uint8_t)(fileSize >> 8);
    fileHeader[4] = (uint8_t)(fileSize >> 16);
    fileHeader[5] = (uint8_t)(fileSize >> 24);
    fileHeader[10] = (uint8_t)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

uint8_t* bitmapInfoHeader(uint32_t height, uint32_t width)
{
    static uint8_t infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[0] = (uint8_t)(INFO_HEADER_SIZE);
    infoHeader[4] = (uint8_t)(width);
    infoHeader[5] = (uint8_t)(width >> 8);
    infoHeader[6] = (uint8_t)(width >> 16);
    infoHeader[7] = (uint8_t)(width >> 24);
    infoHeader[8] = (uint8_t)(height);
    infoHeader[9] = (uint8_t)(height >> 8);
    infoHeader[10] = (uint8_t)(height >> 16);
    infoHeader[11] = (uint8_t)(height >> 24);
    infoHeader[12] = (uint8_t)(1);
    infoHeader[14] = (uint8_t)(BYTES_PER_PIXEL * 8);

    return infoHeader;
}