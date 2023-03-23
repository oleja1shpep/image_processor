#include "matrix_filter.h"

const float EDGE_COEFFICIENT = 4.0;

class EdgeFilter : public MatrixFilter, public GrayFilter {
    std::vector<std::vector<float>> edge_matrix_;

public:
    EdgeFilter();
    Image& Apply(Image& image, const float threshold) const;
};
