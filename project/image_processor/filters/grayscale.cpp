#include "grayscale.h"

Image& GrayFilter::Apply(Image& image) const {
    std::cout << "\x1b[37mApplying \x1b[36m-gs\x1b[37m filter..." << std::endl;

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float gray_color = std::min(1.0f, std::max(0.0f, (RED_COEFICIENT * image.GetPixel(x, y).GetRed() +
                                                              GREEN_COEFICIENT * image.GetPixel(x, y).GetGreen() +
                                                              BLUE_COEFICIENT * image.GetPixel(x, y).GetBlue())));
            image.WritePixelMatrixCords(x, y, Color(gray_color, gray_color, gray_color));
        }
    }
    std::cout << "\x1b[36m-gs\x1b[37m filter has been successfully applied" << std::endl;
    return image;
}
