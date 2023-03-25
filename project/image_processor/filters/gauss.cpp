#include "gauss.h"

namespace {
const float CONST_FROM_WIKI = 6.0f;
const float MAGIC_NUMBER = 2.0f;
const double PI = acos(-1.0);
}  // namespace

Image& GaussFilter::Apply(Image& image, const float sigma) {
    std::cout << "\x1b[37mApplying \x1b[36m-blur\x1b[37m filter..." << std::endl;
    if (sigma < 0.0f) {
        std::cout << "\x1b[31mSigma is less than 0" << std::endl;
        return image;
    }

    int64_t distance = std::ceil((CONST_FROM_WIKI * sigma) / MAGIC_NUMBER);

    PixelMatrix new_pixel_matrix(image.GetHeight(), std::vector<Color>(image.GetWidth()));
    PixelMatrix very_new_pixel_matrix(image.GetHeight(), std::vector<Color>(image.GetWidth()));

    double coef_1 = sqrt(1 / (2 * PI * sigma * sigma));

    std::vector<float> gauss_vector;

    for (int64_t i = 0; i < distance + 1; ++i) {
        gauss_vector.push_back(
            static_cast<float>(coef_1 * std::exp((static_cast<double>(-i * i)) / (2 * sigma * sigma))));
    }

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            const auto& pixel = new_pixel_matrix[y][x];
            float red = pixel.GetRed();
            float green = pixel.GetGreen();
            float blue = pixel.GetBlue();
            for (int64_t i = 0; i < distance + 1; ++i) {
                int64_t y_0 =
                    std::min<int64_t>(static_cast<int64_t>(image.GetHeight()) - 1, std::max<int64_t>(y + i, 0));
                int64_t y_1 =
                    std::min<int64_t>(static_cast<int64_t>(image.GetHeight()) - 1, std::max<int64_t>(y - i, 0));
                const auto& pixel0 = image.GetPixel(x, y_0);
                const float red0 = pixel0.GetRed();
                const float green0 = pixel0.GetGreen();
                const float blue0 = pixel0.GetBlue();

                red += red0 * gauss_vector[i];
                green += green0 * gauss_vector[i];
                blue += blue0 * gauss_vector[i];

                if (i != 0) {
                    const auto& pixel1 = image.GetPixel(x, y_1);
                    const float red1 = pixel1.GetRed();
                    const float green1 = pixel1.GetGreen();
                    const float blue1 = pixel1.GetBlue();

                    red += red1 * gauss_vector[i];
                    green += green1 * gauss_vector[i];
                    blue += blue1 * gauss_vector[i];
                }
            }
            new_pixel_matrix[y][x] = Color(red, green, blue);
        }

        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            const auto& pixel = very_new_pixel_matrix[y][x];
            float red = pixel.GetRed();
            float green = pixel.GetGreen();
            float blue = pixel.GetBlue();
            for (int64_t i = 0; i < distance + 1; ++i) {
                int64_t x_0 =
                    std::min<int64_t>(static_cast<int64_t>(image.GetWidth()) - 1, std::max<int64_t>(x + i, 0));
                int64_t x_1 =
                    std::min<int64_t>(static_cast<int64_t>(image.GetWidth()) - 1, std::max<int64_t>(x - i, 0));

                const auto& pixel0 = new_pixel_matrix[y][x_0];
                const float red0 = pixel0.GetRed();
                const float green0 = pixel0.GetGreen();
                const float blue0 = pixel0.GetBlue();

                red += red0 * gauss_vector[i];
                green += green0 * gauss_vector[i];
                blue += blue0 * gauss_vector[i];

                if (i != 0) {
                    const auto& pixel1 = new_pixel_matrix[y][x_1];
                    const float red1 = pixel1.GetRed();
                    const float green1 = pixel1.GetGreen();
                    const float blue1 = pixel1.GetBlue();

                    red += red1 * gauss_vector[i];
                    green += green1 * gauss_vector[i];
                    blue += blue1 * gauss_vector[i];
                }
            }
            very_new_pixel_matrix[y][x] = Color(red, green, blue);
        }
    }

    image.MovePixelMatrix(very_new_pixel_matrix);

    std::cout << "\x1b[36m-blur\x1b[37m filter has been successfully applied" << std::endl;
    return image;
}
