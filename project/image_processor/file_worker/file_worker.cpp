#include "file_worker.h"

Image FileWorker::ReadIMG(const std::string &path) const {
    Image image;
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "Your file could not be open" << std::endl;
        return image;
    }
    unsigned char file_header[FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);

    if ((file_header[0] != 'B') || (file_header[1] != 'M')) {
        std::cout << "Format of your input file is not .bmp, cannot open file(starts not with 'BM' )" << std::endl;
        f.close();
        return image;
    }

    unsigned char info_header[INFO_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);

    image.WriteFileSize(file_header[FILE_SIZE_INDEX_2] + (file_header[FILE_SIZE_INDEX_3] << BIT_PUSH_8) +
                        (file_header[FILE_SIZE_INDEX_4] << BIT_PUSH_16) +
                        (file_header[FILE_SIZE_INDEX_5] << BIT_PUSH_24));

    image.WriteWidth(info_header[WIDTH_INDEX_4] + (info_header[WIDTH_INDEX_5] << BIT_PUSH_8) +
                     (info_header[WIDTH_INDEX_6] << BIT_PUSH_16) + (info_header[WIDTH_INDEX_7] << BIT_PUSH_24));
    image.WriteHeight(info_header[HEIGHT_INDEX_8] + (info_header[HEIGHT_INDEX_9] << BIT_PUSH_8) +
                      (info_header[HEIGHT_INDEX_10] << BIT_PUSH_16) + (info_header[HEIGHT_INDEX_11] << BIT_PUSH_24));

    PixelMatrix pixel_matrix;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        std::vector<Color> line;
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            line.push_back(Color());
        }
        pixel_matrix.push_back(line);
        line.clear();
    }

    image.WritePixelMatrix(pixel_matrix);

    const int padding_amount = static_cast<int>((4 - ((image.GetWidth() * 3) % 4)) % 4);

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            unsigned char color[3];

            f.read(reinterpret_cast<char *>(color), 3);

            float red = static_cast<float>(color[2]) / COLOR_MAX;
            float green = static_cast<float>(color[1]) / COLOR_MAX;
            float blue = static_cast<float>(color[0]) / COLOR_MAX;

            Color pixel(red, green, blue);
            image.WritePixelMatrixCords(x, y, pixel);
        }
        f.ignore(padding_amount);
    }

    f.close();
    std::cout << "Your file " << path << " has been successfully opened!" << std::endl;

    return image;
}

void FileWorker::ExportIMG(const Image &image, const std::string &path) const {
    if (image.GetFileSize() != 0) {
        std::ofstream f;
        f.open(path, std::ios::out | std::ios::binary);

        if (!f.is_open()) {
            std::cout << "Your file could not be opened" << std::endl;
            return;
        }
        unsigned char bmp_pad[3] = {0, 0, 0};
        const int padding_amount = static_cast<int>((4 - ((image.GetWidth() * 3) % 4)) % 4);

        unsigned char file_header[FILE_HEADER_SIZE];

        file_header[0] = 'B';
        file_header[1] = 'M';

        file_header[FILE_SIZE_INDEX_2] = image.GetFileSize();
        file_header[FILE_SIZE_INDEX_3] = image.GetFileSize() >> BIT_PUSH_8;
        file_header[FILE_SIZE_INDEX_4] = image.GetFileSize() >> BIT_PUSH_16;
        file_header[FILE_SIZE_INDEX_5] = image.GetFileSize() >> BIT_PUSH_24;

        for (int i = TRASH_INDEX_6; i < TRASH_INDEX_13 + 1; ++i) {
            if (i != FILE_INFO_INDEX_10) {
                file_header[i] = 0;
            } else {
                file_header[FILE_INFO_INDEX_10] = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
            }
        }

        unsigned char info_header[INFO_HEADER_SIZE];
        info_header[0] = INFO_HEADER_SIZE;
        info_header[1] = 0;
        info_header[TRASH_INDEX_2] = 0;
        info_header[TRASH_INDEX_3] = 0;

        info_header[WIDTH_INDEX_4] = image.GetWidth();
        info_header[WIDTH_INDEX_5] = image.GetWidth() >> BIT_PUSH_8;
        info_header[WIDTH_INDEX_6] = image.GetWidth() >> BIT_PUSH_16;
        info_header[WIDTH_INDEX_7] = image.GetWidth() >> BIT_PUSH_24;

        info_header[HEIGHT_INDEX_8] = image.GetHeight();
        info_header[HEIGHT_INDEX_9] = image.GetHeight() >> BIT_PUSH_8;
        info_header[HEIGHT_INDEX_10] = image.GetHeight() >> BIT_PUSH_16;
        info_header[HEIGHT_INDEX_11] = image.GetHeight() >> BIT_PUSH_24;

        info_header[TRASH_INDEX_12] = 1;
        info_header[TRASH_INDEX_13] = 0;

        info_header[BITS_INDEX] = BITS_PER_PIXEL;

        for (int i = TRASH_INDEX_15; i < TRASH_INDEX_40; ++i) {
            info_header[i] = 0;
        }
        f.write(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
        f.write(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);

        for (int y = 0; y < image.GetHeight(); ++y) {
            for (int x = 0; x < image.GetWidth(); ++x) {
                unsigned char red = static_cast<unsigned char>(image.GetPixel(x, y).GetRed() * COLOR_MAX);
                unsigned char green = static_cast<unsigned char>(image.GetPixel(x, y).GetGreen() * COLOR_MAX);
                unsigned char blue = static_cast<unsigned char>(image.GetPixel(x, y).GetBlue() * COLOR_MAX);

                unsigned char color[3] = {blue, green, red};

                f.write(reinterpret_cast<char *>(color), 3);
            }
            f.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
        }
        f.close();
        std::cout << "Your file has been successfully saved to " << path << std::endl;
    }
}
