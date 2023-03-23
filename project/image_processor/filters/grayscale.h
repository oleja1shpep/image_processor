#pragma once

#include "../image/image.h"

const float RED_COEFICIENT = 0.299f;
const float GREEN_COEFICIENT = 0.586f;
const float BLUE_COEFICIENT = 0.114f;

class GrayFilter {
public:
    Image& Apply(Image& image) const;
};
