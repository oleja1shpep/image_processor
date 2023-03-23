#pragma once

#include "grayscale.h"
#include "../image/image.h"

class MatrixFilter {
public:
    Image& ApplyMatrixFilter(Image& image, const std::vector<std::vector<float>>& matrix) const;
};
