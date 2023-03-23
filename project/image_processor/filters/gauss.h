#include "../image/image.h"
#include <cmath>

class GaussFilter {
public:
    Image& Apply(Image& image, const float sigma);
};
