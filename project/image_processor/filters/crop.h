#include "../image/image.h"

class CropFilter {
    const size_t crop_width_;
    const size_t crop_height_;

public:
    explicit CropFilter(const size_t w, const size_t h);
    Image& Apply(Image& image) const;
};
