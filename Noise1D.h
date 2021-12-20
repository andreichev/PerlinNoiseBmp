//
// Created by Admin on 19.12.2021.
//

#pragma once

float interpolate(float v1, float v2, float blend) {
    return (v2 - v1) * blend + v1;
}

void generatePerlinNoise1DV2(unsigned seedValue, int octaves, float bias, int width, float* values) {
    srandom(seedValue);
    random();

    float seed[width];
    for(int x = 0; x < width; x++) {
        seed[x] = ((float) random() / (float) RAND_MAX);
        values[x] = 0;
    }

    for(int x = 0; x < width; x++) {
        float scale = 1.0f;
        float scaleAccumulation = 0.0f;
        for (int o = 0; o < octaves; o++) {
            int dist = width >> o;
            int sample1 = (x / dist) * dist;
            int sample2 = (sample1 + dist) % width;

            float blend = (float) (x - sample1) / (float) (dist);
            float sample = interpolate(seed[sample1], seed[sample2], blend);
            values[x] += sample * scale;

            scaleAccumulation += scale;
            scale /= bias;
        }
        values[x] /= scaleAccumulation;
    }
}

void generatePerlinNoise1DV1(unsigned seedValue, int octaves, float bias, int width, float* values) {
    srandom(seedValue);
    random();

    float seed[width];
    for(int x = 0; x < width; x++) {
        seed[x] = ((float) random() / (float) RAND_MAX);
        values[x] = 0;
    }

    float scale = 1.0f;
    float scaleAccumulation = 0.0f;
    for(int o = 0; o < octaves; o++) {
        int dist = width >> o;
        for (int x = 0; x < width; x++) {
            int sample1 = (x / dist) * dist;
            int sample2 = (sample1 + dist) % width;
            float blend = (float) (x - sample1) / (float) (dist);
            float sample = interpolate(seed[sample1], seed[sample2], blend);
            values[x] += sample * scale;
        }
        scaleAccumulation += scale;
        scale /= bias;
    }
    for (int x = 0; x < width; x++) {
        values[x] /= scaleAccumulation;
    }
}
