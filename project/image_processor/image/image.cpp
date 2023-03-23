#include "image.h"

Color::Color(const float red, const float green, const float blue) {
    red_ = red;
    green_ = green;
    blue_ = blue;
}

bool Color::operator==(const Color& color2) const {
    if (std::abs(this->red_ - color2.red_) > EPS) {
        return false;
    }
    if (std::abs(this->green_ - color2.green_) > EPS) {
        return false;
    }
    if (std::abs(this->blue_ - color2.blue_) > EPS) {
        return false;
    }
    return true;
}

bool Color::operator!=(const Color& color2) const {
    return !(*this == color2);
}

Color Color::operator+(const Color& color2) const {
    Color color(0, 0, 0);
    color.red_ = this->red_ + color2.red_;
    color.green_ = this->green_ + color2.green_;
    color.blue_ = this->blue_ + color2.blue_;
    return color;
}

Color Color::operator-(const Color& color2) const {
    Color color(0, 0, 0);
    color.red_ = this->red_ - color2.red_;
    color.green_ = this->green_ - color2.green_;
    color.blue_ = this->blue_ - color2.blue_;
    return color;
}

Color Color::operator*(const float coeff) const {
    Color color(0, 0, 0);
    color.red_ = this->red_ * coeff;
    color.green_ = this->green_ * coeff;
    color.blue_ = this->blue_ * coeff;
    return color;
}

Color& Color::operator+=(const Color& color2) {
    *this = *this + color2;
    return *this;
}

float Color::GetRed() const {
    return red_;
}
float Color::GetGreen() const {
    return green_;
}
float Color::GetBlue() const {
    return blue_;
}

void Color::WriteRed(const float color) {
    red_ = color;
}
void Color::WriteGreen(const float color) {
    green_ = color;
}
void Color::WriteBlue(const float color) {
    blue_ = color;
}

Image::Image() {
}

Image::Image(const size_t width, const size_t height) {
    width_ = width;
    height_ = height;
}

size_t Image::GetFileSize() const {
    return file_size_;
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

PixelMatrix Image::GetPixelMatrix() const {
    return pixel_matrix_;
}

void Image::WriteFileSize(const size_t file_size) {
    file_size_ = file_size;
}

void Image::WriteHeight(const size_t height) {
    height_ = height;
}

void Image::WriteWidth(const size_t width) {
    width_ = width;
}

void Image::WritePixelMatrix(const PixelMatrix& pixel_matrix) {
    pixel_matrix_ = pixel_matrix;
}

void Image::WritePixelMatrixCords(const size_t x, const size_t y, const Color& color) {
    pixel_matrix_[y][x] = color;
}

const Color& Image::GetPixel(const size_t x, const size_t y) const {
    return pixel_matrix_[y][x];
}

bool Image::operator==(const Image& image2) const {
    if (this->width_ != image2.width_) {
        return false;
    }

    if (this->height_ != image2.height_) {
        return false;
    }

    for (size_t y = 0; y < this->height_; ++y) {
        for (size_t x = 0; x < this->width_; ++x) {
            if (this->pixel_matrix_[y][x] != image2.pixel_matrix_[y][x]) {
                return false;
            }
        }
    }
    return true;
}

bool Image::operator!=(const Image& image2) const {
    return !(*this == image2);
}

void Image::MovePixelMatrix(PixelMatrix& pixel_matrix) {
    pixel_matrix_ = std::move(pixel_matrix);
}
