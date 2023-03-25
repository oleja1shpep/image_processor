#include "vignette.h"
#include <cmath>

Image& VignetteFilter::Apply(Image& image, const int64_t diameter, const float power) const {
    std::cout << "\x1b[37mApplying \x1b[36m-vignette\x1b[37m filter..." << std::endl;
    PixelMatrix new_pixel_matrix = image.GetPixelMatrix();

    size_t center_x = image.GetWidth() / 2;
    size_t center_y = image.GetHeight() / 2;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            double distance = sqrt((static_cast<double>(center_x) - static_cast<double>(x)) *
                                       (static_cast<double>(center_x) - static_cast<double>(x)) +
                                   (static_cast<double>(center_y) - static_cast<double>(y)) *
                                       (static_cast<double>(center_y) - static_cast<double>(y)));
            if (distance > static_cast<double>(diameter / 2)) {
                new_pixel_matrix[y][x] =
                    new_pixel_matrix[y][x] *
                    static_cast<float>(
                        pow((1 - (distance - static_cast<float>(diameter) / 2) /
                                     (static_cast<float>(std::max<size_t>(image.GetHeight(), image.GetWidth())) -
                                      static_cast<float>(diameter / 2))),
                            power));

                new_pixel_matrix[y][x].WriteRed(
                    std::min<float>(1, std::max<float>(0, new_pixel_matrix[y][x].GetRed())));
                new_pixel_matrix[y][x].WriteGreen(
                    std::min<float>(1, std::max<float>(0, new_pixel_matrix[y][x].GetGreen())));
                new_pixel_matrix[y][x].WriteGreen(
                    std::min<float>(1, std::max<float>(0, new_pixel_matrix[y][x].GetGreen())));
            }
        }
    }

    image.WritePixelMatrix(new_pixel_matrix);
    std::cout << "\x1b[36m-vignette\x1b[37m filter has been successfully applied!" << std::endl;
    return image;
}
