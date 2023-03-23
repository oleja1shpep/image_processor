#include "matrix_filter.h"

Image& MatrixFilter::ApplyMatrixFilter(Image& image, const std::vector<std::vector<float>>& matrix) const {
    PixelMatrix new_pixel_matrix(image.GetHeight(), std::vector<Color>(image.GetWidth(), Color()));

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            for (int64_t i = -1; i < 2; ++i) {
                int64_t x_0 =
                    std::min<int64_t>(static_cast<int64_t>(image.GetWidth() - 1), std::max<int64_t>(x + i, 0));
                for (int64_t j = -1; j < 2; ++j) {
                    int64_t y_0 =
                        std::min<int64_t>(static_cast<int64_t>(image.GetHeight() - 1), std::max<int64_t>(y + j, 0));
                    new_pixel_matrix[y][x] += (image.GetPixel(x_0, y_0) * matrix[j + 1][i + 1]);
                }
            }
        }
    }

    image.WritePixelMatrix(new_pixel_matrix);

    return image;
}
