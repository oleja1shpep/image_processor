#include "sharp.h"

const float SHARP_COEFFICIENT = 5.0;

SharpFilter::SharpFilter() {
    sharp_matrix_ = {{0.0, -1.0, 0.0}, {-1.0, SHARP_COEFFICIENT, -1.0}, {0.0, -1.0, 0.0}};
}

Image& SharpFilter::Apply(Image& image) const {
    std::cout << "applying -sharp filter..." << std::endl;
    ApplyMatrixFilter(image, sharp_matrix_);

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color color(std::min<float>(1.0f, std::max<float>(0.0, image.GetPixel(x, y).GetRed())),
                        std::min<float>(1.0f, std::max<float>(0.0, image.GetPixel(x, y).GetGreen())),
                        std::min<float>(1.0f, std::max<float>(0.0, image.GetPixel(x, y).GetBlue())));
            image.WritePixelMatrixCords(x, y, color);
        }
    }

    std::cout << "-sharp filter has been successfully applied" << std::endl;

    return image;
}
