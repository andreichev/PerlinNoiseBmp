//
// Created by Admin on 19.12.2021.
//

#pragma once

#include <fstream>

struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + 786432;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;

    void save_on_file(std::ofstream& out);
} bmpHeader;

void BmpHeader::save_on_file(std::ofstream& fout) {
    fout.write(this->bitmapSignatureBytes, 2);
    fout.write((char*)&this->sizeOfBitmapFile, sizeof(uint32_t));
    fout.write((char*)&this->reservedBytes, sizeof(uint32_t));
    fout.write((char*)&this->pixelDataOffset, sizeof(uint32_t));
}

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 512; // in pixels
    int32_t height = 512; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;

    void save_on_file(std::ofstream& fout);
} bmpInfoHeader;

void BmpInfoHeader::save_on_file(std::ofstream& fout) {
    fout.write((char*)&this->sizeOfThisHeader, sizeof(uint32_t));
    fout.write((char*)&this->width, sizeof(int32_t));
    fout.write((char*)&this->height, sizeof(int32_t));
    fout.write((char*)&this->numberOfColorPlanes, sizeof(uint16_t));
    fout.write((char*)&this->colorDepth, sizeof(uint16_t));
    fout.write((char*)&this->compressionMethod, sizeof(uint32_t));
    fout.write((char*)&this->rawBitmapDataSize, sizeof(uint32_t));
    fout.write((char*)&this->horizontalResolution, sizeof(int32_t));
    fout.write((char*)&this->verticalResolution, sizeof(int32_t));
    fout.write((char*)&this->colorTableEntries, sizeof(uint32_t));
    fout.write((char*)&this->importantColors, sizeof(uint32_t));
}

struct Pixel {
    uint8_t blue = 255;
    uint8_t green = 255;
    uint8_t red = 0;
    void save_on_file(std::ofstream& fout);
};

void Pixel::save_on_file(std::ofstream& fout) {
    fout.write((char*)&this->blue, sizeof(uint8_t));
    fout.write((char*)&this->green, sizeof(uint8_t));
    fout.write((char*)&this->red, sizeof(uint8_t));
}

size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
size_t width = bmpInfoHeader.width;
size_t height = bmpInfoHeader.height;

void saveBmpToFile(const char* name, Pixel* pixels) {
    std::ofstream out(name, std::ios::binary);

    bmpHeader.save_on_file(out);
    bmpInfoHeader.save_on_file(out);

    for (int i = 0; i < numberOfPixels; i++) {
        pixels[i].save_on_file(out);
    }
    out.close();
}