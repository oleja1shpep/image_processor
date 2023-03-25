#include "../filters/negative.h"
#include "../filters/grayscale.h"
#include "../file_worker/file_worker.h"
#include "../filters/crop.h"
#include "../filters/sharp.h"
#include "../filters/edge.h"
#include "../filters/gauss.h"
#include "../filters/vignette.h"
#include <iostream>
#include <cstdio>

const std::string FLAG_PATH = "../project/image_processor/unit_tests/data/flag.bmp";
const std::string LENNA_PATH = "../project/image_processor/unit_tests/data/lenna.bmp";

int main() {
    FileWorker file_worker;

    // flag_neg.bmp test

    {
        NegativeFilter neg;
        Image image = file_worker.ReadIMG(FLAG_PATH);
        neg.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/flag_neg.bmp");
        assert(image == control_image);
    }

    // flag_crop.bmp test

    {
        CropFilter crop(100, 100);
        Image image = file_worker.ReadIMG(FLAG_PATH);
        crop.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/flag_crop.bmp");

        assert(image == control_image);
    }

    // flag_gray.bmp test

    {
        GrayFilter gray;
        Image image = file_worker.ReadIMG(FLAG_PATH);
        gray.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/flag_gs.bmp");

        assert(image == control_image);
    }

    // flag_edge.bmp test

    {
        EdgeFilter edge;
        Image image = file_worker.ReadIMG(FLAG_PATH);
        edge.Apply(image, 0.1);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/flag_edge.bmp");

        assert(image == control_image);
    }

    // flag_edge_edge.bmp test

    {
        EdgeFilter edge;
        Image image = file_worker.ReadIMG(FLAG_PATH);
        edge.Apply(image, 0.1);
        edge.Apply(image, 0.1);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/flag_edge_edge.bmp");

        assert(image == control_image);
    }

    // flag_sharp.bmp test

    {
        SharpFilter sharp;
        Image image = file_worker.ReadIMG(FLAG_PATH);
        sharp.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/flag_sharp.bmp");

        assert(image == control_image);
    }

    // lenna filters
    // lenna_neg.bmp test

    {
        NegativeFilter neg;
        Image image = file_worker.ReadIMG(LENNA_PATH);
        neg.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_neg.bmp");
        assert(image == control_image);
    }

    // lenna_neg_neg.bmp test

    {
        NegativeFilter neg;
        Image image = file_worker.ReadIMG(LENNA_PATH);
        neg.Apply(image);
        neg.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_neg_neg.bmp");
        assert(image == control_image);
    }

    // lenna_crop.bmp test 1

    {
        CropFilter crop(100000, 100000);
        Image image = file_worker.ReadIMG(LENNA_PATH);
        crop.Apply(image);
        Image control_image = file_worker.ReadIMG(LENNA_PATH);

        assert(image == control_image);
    }

    // lenna_gs.bmp test

    {
        GrayFilter gray;
        Image image = file_worker.ReadIMG(LENNA_PATH);
        gray.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_gs.bmp");

        assert(image == control_image);
    }

    // lenna_gs_gs.bmp test

    {
        GrayFilter gray;
        Image image = file_worker.ReadIMG(LENNA_PATH);
        gray.Apply(image);
        gray.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_gs_gs.bmp");

        assert(image == control_image);
    }

    // lenna_crop.test 2

    {
        CropFilter crop(999, 1999);
        Image image = file_worker.ReadIMG(LENNA_PATH);
        crop.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_crop.bmp");

        assert(image == control_image);
    }

    // lenna_crop_crop.test 3

    {
        CropFilter crop(100, 1);
        Image image = file_worker.ReadIMG(LENNA_PATH);
        crop.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_crop_crop.bmp");

        assert(image == control_image);
    }

    // lenna_sharp.bmp test

    {
        Image image = file_worker.ReadIMG(LENNA_PATH);
        SharpFilter sharp;
        sharp.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_sharp.bmp");
        assert(image == control_image);
    }

    // lenna_sharp_sharp.bmp test

    {
        Image image = file_worker.ReadIMG(LENNA_PATH);
        SharpFilter sharp;
        sharp.Apply(image);
        sharp.Apply(image);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_sharp_sharp.bmp");
        assert(image == control_image);
    }

    // lenna_blur.bmp test

    {
        Image image = file_worker.ReadIMG(LENNA_PATH);
        GaussFilter blur;
        blur.Apply(image, 7.5);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_blur.bmp");
        assert(image == control_image);
    }

    // lenna_blur_blur.bmp test

    {
        Image image = file_worker.ReadIMG(LENNA_PATH);
        GaussFilter blur;
        blur.Apply(image, 7.5);
        blur.Apply(image, 3);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_blur_blur.bmp");
        assert(image == control_image);
    }

    // test read

    {
        Image image;
        std::ifstream f;
        f.open(FLAG_PATH, std::ios::in | std::ios::binary);

        assert(f.is_open());

        unsigned char file_header[FILE_HEADER_SIZE];
        f.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);

        assert((file_header[0] == 'B') && (file_header[1] == 'M'));

        unsigned char info_header[INFO_HEADER_SIZE];
        f.read(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);

        image.WriteFileSize(file_header[FILE_SIZE_INDEX_2] + (file_header[FILE_SIZE_INDEX_3] << BIT_PUSH_8) +
                            (file_header[FILE_SIZE_INDEX_4] << BIT_PUSH_16) +
                            (file_header[FILE_SIZE_INDEX_5] << BIT_PUSH_24));

        image.WriteWidth(info_header[WIDTH_INDEX_4] + (info_header[WIDTH_INDEX_5] << BIT_PUSH_8) +
                         (info_header[WIDTH_INDEX_6] << BIT_PUSH_16) + (info_header[WIDTH_INDEX_7] << BIT_PUSH_24));
        image.WriteHeight(info_header[HEIGHT_INDEX_8] + (info_header[HEIGHT_INDEX_9] << BIT_PUSH_8) +
                          (info_header[HEIGHT_INDEX_10] << BIT_PUSH_16) +
                          (info_header[HEIGHT_INDEX_11] << BIT_PUSH_24));

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

        assert(!pixel_matrix.empty());

        const int padding_amount = static_cast<int>((4 - ((image.GetWidth() * 3) % 4)) % 4);

        for (size_t y = 0; y < image.GetHeight(); ++y) {
            for (size_t x = 0; x < image.GetWidth(); ++x) {
                unsigned char color[3];

                f.read(reinterpret_cast<char *>(color), 3);

                float red = static_cast<float>(color[2]) / COLOR_MAX;
                float green = static_cast<float>(color[1]) / COLOR_MAX;
                float blue = static_cast<float>(color[0]) / COLOR_MAX;

                assert((red <= 1.0) && (green <= 1.0) && (blue <= 1.0));
                assert((red >= 0.0) && (green >= 0.0) && (blue >= 0.0));

                Color pixel(red, green, blue);
                image.WritePixelMatrixCords(x, y, pixel);
            }
            f.ignore(padding_amount);
        }

        assert(!image.GetPixelMatrix().empty());
        assert(image.GetPixelMatrix() != pixel_matrix);

        f.close();

        Image control_image = file_worker.ReadIMG(FLAG_PATH);

        assert(image == control_image);
    }

    // test 1 pixel image

    {
        Image image;
        image.WriteHeight(1);
        image.WriteWidth(1);
        Color color(1, 1, 1);
        image.WritePixelMatrix({{color}});
        const int padding = static_cast<int>((4 - ((static_cast<int64_t>(image.GetWidth()) * 3) % 4)) % 4);
        image.WriteFileSize(FILE_HEADER_SIZE + INFO_HEADER_SIZE + image.GetWidth() * image.GetHeight() * 3 +
                            padding * image.GetHeight());
        file_worker.ExportIMG(image, "output_test.bmp");
        Image control_image = file_worker.ReadIMG("output_test.bmp");

        remove("output_test.bmp");
        assert(control_image == image);
    }

    // test write

    {
        Image image = file_worker.ReadIMG(FLAG_PATH);
        file_worker.ExportIMG(image, "output_test.bmp");
        Image control_image = file_worker.ReadIMG("output_test.bmp");

        remove("output_test.bmp");
        assert(image == control_image);
    }

    // test lenna_vignette

    {
        Image image = file_worker.ReadIMG(LENNA_PATH);
        VignetteFilter vignette;
        vignette.Apply(image, 1300, 4);
        Image control_image = file_worker.ReadIMG("../project/image_processor/unit_tests/data/lenna_vignette.bmp");
        assert(image == control_image);
    }

    return 0;
}
