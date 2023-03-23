#include "../image/image.h"

class VignetteFilter {
public:
    Image& Apply(Image& image, const int64_t diameter, const float power) const;
};
