//
// Created by Admin on 20.12.2021.
//

#pragma once

float interpolate(float v1, float v2, float blend) {
    return (v2 - v1) * blend + v1;
}

void generatePerlinNoise2D(unsigned seedValue, int octaves, float bias, int width, int height, float* values) {
    srandom(seedValue);
    random();

    float seed[width * height];
    for(int i = 0; i < width * height; i++) {
        seed[i] = ((float) random() / (float) RAND_MAX);
    }

    for(int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float scale = 1.0f;
            float scaleAccumulation = 0.0f;
            values[y * width + x] = 0;
            for (int o = 0; o < octaves; o++) {
                int dist = width >> o;
                int sampleX1 = (x / dist) * dist;
                int sampleY1 = (y / dist) * dist;

                int sampleX2 = (sampleX1 + dist) % width;
                int sampleY2 = (sampleY1 + dist) % width;

                float blendX = (float) (x - sampleX1) / (float) (dist);
                float blendY = (float) (y - sampleY1) / (float) (dist);

                float sampleT = interpolate(seed[sampleY1 * width + sampleX1], seed[sampleY1 * width + sampleX2], blendX);
                float sampleB = interpolate(seed[sampleY2 * width + sampleX1], seed[sampleY2  * width + sampleX2], blendX);
                values[y * width + x] += (blendY * (sampleB - sampleT) + sampleT) * scale;

                scaleAccumulation += scale;
                scale /= bias;
            }
            values[y * width + x] /= scaleAccumulation;
        }
    }
}