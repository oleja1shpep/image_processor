#include "../image/image.h"

const int BIT_PUSH_8 = 8;
const int BIT_PUSH_16 = 16;
const int BIT_PUSH_24 = 24;

const int FILE_SIZE_INDEX_2 = 2;
const int FILE_SIZE_INDEX_3 = 3;
const int FILE_SIZE_INDEX_4 = 4;
const int FILE_SIZE_INDEX_5 = 5;

const int WIDTH_INDEX_4 = 4;
const int WIDTH_INDEX_5 = 5;
const int WIDTH_INDEX_6 = 6;
const int WIDTH_INDEX_7 = 7;

const int HEIGHT_INDEX_8 = 8;
const int HEIGHT_INDEX_9 = 9;
const int HEIGHT_INDEX_10 = 10;
const int HEIGHT_INDEX_11 = 11;

const int TRASH_INDEX_2 = 2;
const int TRASH_INDEX_3 = 3;
const int TRASH_INDEX_6 = 6;
const int TRASH_INDEX_12 = 12;
const int TRASH_INDEX_13 = 13;
const int TRASH_INDEX_15 = 15;
const int TRASH_INDEX_40 = 40;

const int BITS_INDEX = 14;

const int FILE_INFO_INDEX_10 = 10;

const float COLOR_MAX = 255.0f;

const int BITS_PER_PIXEL = 24;

class FileWorker {
public:
    Image ReadIMG(const std::string& path) const;
    void ExportIMG(const Image& image, const std::string& path) const;
};
