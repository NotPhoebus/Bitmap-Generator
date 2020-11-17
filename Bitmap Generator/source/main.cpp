#include <iostream>
#include <cstdint>
#include <string>

#include "bitmap_generator.h"

int main()
{
    std::cout << "Enter File Name: ";
    std::string imageFileName;
    std::cin >> imageFileName;
    std::string filename = imageFileName + ".bmp";

    std::cout << "Enter amount of images to generate: ";
    uint32_t timesToGenerate;
    std::cin >> timesToGenerate;

    constexpr uint32_t height = 255;
    constexpr uint32_t width = 255;
    uint8_t image[height][width][BYTES_PER_PIXEL];

    for (uint32_t i = 1; i <= timesToGenerate; i++)
    {
        for (uint8_t x = 0; x < width; x++)
            for (uint8_t y = 0; y < height; y++) {
                image[x][y][RED] = (x >= width / 2 && i >= 1) ? 255 : 0;
                image[x][y][GREEN] = (y >= height / 2 && i >= 2) ? 255 : 0;
                image[x][y][BLUE] = (x >= width / 2 || y >= height / 2 && i >= 3) ? 255 : 0;
            }
        bitmap((uint8_t*)image, height, width, filename);
        std::cout << filename << " generated!\n";
        filename = imageFileName + std::to_string(i) + ".bmp";
    }
    system("pause");
    std::cout << "Done";
}