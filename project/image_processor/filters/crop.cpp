#include "crop.h"

CropFilter::CropFilter(const size_t w, const size_t h) : crop_width_(w), crop_height_(h) {
}

Image& CropFilter::Apply(Image& image) const {
    std::cout << "applying -crop filter..." << std::endl;
    size_t applied_height = std::min<size_t>(crop_height_, image.GetHeight());
    size_t applied_width = std::min<size_t>(crop_width_, image.GetWidth());

    PixelMatrix pixel_matrix = image.GetPixelMatrix();

    std::reverse(pixel_matrix.begin(), pixel_matrix.end());

    pixel_matrix.resize(applied_height);

    for (std::vector<Color>& line : pixel_matrix) {
        line.resize(applied_width);
    }

    std::reverse(pixel_matrix.begin(), pixel_matrix.end());

    image.WritePixelMatrix(pixel_matrix);
    image.WriteHeight(applied_height);
    image.WriteWidth(applied_width);

    const int padding_amount = static_cast<int>((4 - ((applied_width * 3) % 4)) % 4);
    image.WriteFileSize(FILE_HEADER_SIZE + INFO_HEADER_SIZE + applied_width * applied_height * 3 +
                        padding_amount * applied_height);
    std::cout << "-crop filter has been successfully applied" << std::endl;
    return image;
}
