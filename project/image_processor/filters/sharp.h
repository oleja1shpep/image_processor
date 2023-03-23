#include "matrix_filter.h"

class SharpFilter : public MatrixFilter {
    std::vector<std::vector<float>> sharp_matrix_;

public:
    SharpFilter();
    Image& Apply(Image& image) const;
};
