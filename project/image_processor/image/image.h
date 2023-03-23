#pragma once

#include <vector>
#include <fstream>
#include <iostream>

const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

const float EPS = 0.005;

class Color {
    float red_ = 0;
    float green_ = 0;
    float blue_ = 0;

public:
    explicit Color(const float red = 0, const float green = 0, const float blue = 0);

    Color operator+(const Color& color2) const;
    Color operator-(const Color& color2) const;
    Color operator*(const float coeff) const;

    Color& operator+=(const Color& color2);

    bool operator==(const Color& color2) const;
    bool operator!=(const Color& color2) const;

    float GetRed() const;
    float GetGreen() const;
    float GetBlue() const;

    void WriteRed(const float color);
    void WriteGreen(const float color);
    void WriteBlue(const float color);
};

using PixelMatrix = std::vector<std::vector<Color>>;

class Image {
    size_t file_size_ = 0;
    size_t width_ = 0;
    size_t height_ = 0;
    PixelMatrix pixel_matrix_ = {};

public:
    Image();
    explicit Image(const size_t width, const size_t height);

    size_t GetFileSize() const;
    size_t GetWidth() const;
    size_t GetHeight() const;
    PixelMatrix GetPixelMatrix() const;
    const Color& GetPixel(const size_t x, const size_t y) const;

    void WriteFileSize(const size_t file_size);
    void WriteWidth(const size_t width);
    void WriteHeight(const size_t height);
    void WritePixelMatrix(const PixelMatrix& pixel_matrix);
    void WritePixelMatrixCords(const size_t x, const size_t y, const Color& color);
    void MovePixelMatrix(PixelMatrix& pixel_matrix);

    bool operator==(const Image& image2) const;
    bool operator!=(const Image& image2) const;
};
