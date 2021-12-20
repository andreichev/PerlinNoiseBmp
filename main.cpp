#include <iostream>
#include "FunctionTimer.h"
#include "Noise1D.h"
#include "BMP.h"

#define scan(x) std::cin >> x
#define print(x) std::cout << x
#define println(x) std::cout << x; std::cout << std::endl
#define newLine std::cout << std::endl

int main() {
    Pixel pixels[numberOfPixels];

    float heights[width];

    CALL_AND_CAPTURE_TIME(generatePerlinNoise1DV1(45443, 10, 2.0f, width, heights));

    for (int i = 0; i < numberOfPixels; i++) {
        int x = i % (int) width;
        int y = i / (int) width;

        unsigned char color = 255;
        if((float) y > heights[x] * height) {
            color = 0;
        }

        pixels[i].red = color;
        pixels[i].green = color;
        pixels[i].blue = color;
    }

    saveBmpToFile("../output.bmp", pixels);
}