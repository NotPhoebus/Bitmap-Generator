#pragma once

#define RED 2
#define GREEN 1
#define BLUE  0
#define BYTES_PER_PIXEL 3 /// red, green, & blue
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

void bitmap(uint8_t* image, uint32_t height, uint32_t width, std::string imageFileName);
uint8_t* bitmapFileHeader(uint32_t height, uint32_t stride);
uint8_t* bitmapInfoHeader(uint32_t height, uint32_t width);