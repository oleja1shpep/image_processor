#include "edge.h"

EdgeFilter::EdgeFilter() {
    edge_matrix_ = {{0.0, -1.0, 0.0}, {-1.0, EDGE_COEFFICIENT, -1.0}, {0.0, -1.0, 0.0}};
}

Image& EdgeFilter::Apply(Image& image, const float threshold) const {
    std::cout << "\x1b[37mApplying \x1b[36m-edge\x1b[37m filter..." << std::endl;
    GrayFilter::Apply(image);

    ApplyMatrixFilter(image, edge_matrix_);

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float final_color = std::min<float>(1.0f, std::max<float>(0.0, image.GetPixel(x, y).GetRed()));

            if (final_color > threshold) {
                Color color(1.0, 1.0, 1.0);
                image.WritePixelMatrixCords(x, y, color);
            } else {
                Color color(0.0, 0.0, 0.0);
                image.WritePixelMatrixCords(x, y, color);
            }
        }
    }

    std::cout << "\x1b[36m-edge\x1b[37m filter has been successfully applied" << std::endl;
    return image;
}
