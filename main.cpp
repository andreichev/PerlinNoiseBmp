#define ONE_DIMENSIONAL 0

#include "FunctionTimer.h"
#include "BMP.h"

#if ONE_DIMENSIONAL

#include "Noise1D.h"
#else

#include "Noise2D.h"


#endif

int main() {
    Pixel pixels[numberOfPixels];

#if ONE_DIMENSIONAL
    float heights[width];

    CALL_AND_CAPTURE_TIME(generatePerlinNoise1DV1(345, 10, 2.0f, width, heights));

    for (int i = 0; i < numberOfPixels; i++) {
        int x = i % (int) width;
        int y = i / (int) width;

        unsigned char color = 255;
        if ((float) y > heights[x] * height) {
            color = 0;
        }

        pixels[i].red = color;
        pixels[i].green = color;
        pixels[i].blue = color;
    }

    saveBmpToFile("../output1D.bmp", pixels);
#else
    float values[width * height];

    CALL_AND_CAPTURE_TIME(generatePerlinNoise2D(345, 7, 1.5f, width, height, values));

    for (int i = 0; i < numberOfPixels; i++) {
        auto color = (unsigned char) (values[i] * 255);

        pixels[i].red = color;
        pixels[i].green = color;
        pixels[i].blue = color;
    }

    saveBmpToFile("../output2D.bmp", pixels);
#endif
}