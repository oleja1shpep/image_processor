#include "filters/negative.h"
#include "filters/grayscale.h"
#include "file_worker/file_worker.h"
#include "filters/crop.h"
#include "filters/sharp.h"
#include "filters/edge.h"
#include "filters/gauss.h"
#include "filters/vignette.h"
#include <iostream>

bool IsStringNumber(std::string& string) {
    for (const char letter : string) {
        if (!isdigit(letter)) {
            return false;
        }
    }
    return true;
}

bool IsStringFloat(std::string& string) {
    if (string[0] == '-') {
        string = string.substr(1, string.size() - 1);
    }
    size_t dot_counter = 0;
    for (const char& letter : string) {
        if (letter == '.') {
            dot_counter += 1;
            if (dot_counter > 1) {
                return false;
            }
        }
    }

    for (const char& letter : string) {
        if (!(isdigit(letter) || letter == '.')) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {

    if (argc == 1) {
        std::cout << "\x1b[35m\n\nImage Processor \x1b[0m \n"
                     "\x1b[33m\nSimple console app to apply filters on your photos\x1b[0m"
                     "\x1b[31m\n<IMPORTANT: images should be 24-bit .bmp files>\x1b[0m\n"
                     "\x1b[33m\nUsage:\x1b[0m\n"
                     "\x1b[37m     ./image_processor input.bmp output.bmp\x1b[36m -[filter1]\x1b[33m {arg1_1} {agr1_2}..\x1b[36m -[filter2]\x1b[33m {arg2_1} {arg2_2} ...\x1b[0m\n"
                     "\x1b[33m\nExample:\n"
                     "\x1b[37m     ./image_processor input.bmp output.bmp\x1b[36m -gs -blur\x1b[33m 4\x1b[36m -edge\x1b[33m 0.1\x1b[36m -crop\x1b[33m 1000 1000\x1b[0m\n"
                     "\x1b[31m\n<IMPORTANT: you can use relative paths from \"/build\" directory or absolute paths>\n\x1b[33m\n"
                     "Commands:\n"
                     "\x1b[36m    -neg                        \x1b[35m|\x1b[37m  Negative filter\n"
                     "\x1b[36m    -gs                        \x1b[35m |\x1b[37m  Grayscale filter\n"
                     "\x1b[36m    -sharp                     \x1b[35m |\x1b[37m  Sharpening filter\n"
                     "\x1b[36m    -edge\x1b[33m <threshold>          \x1b[35m |\x1b[37m  Edge detection filter\n"
                     "\x1b[36m    -crop\x1b[33m <width, height>      \x1b[35m |\x1b[37m  Crop filter\n"
                     "\x1b[36m    -blur\x1b[33m <sigma>              \x1b[35m |\x1b[37m  Gauss blur filter(takes a little bit too long)\n"
                     "\x1b[36m    -vignette\x1b[33m <diameter, power> \x1b[35m|\x1b[37m  Vignette filter\n\x1b[0m\n"
                  << std::endl;
        return 0;
    }

    if (argc == 2) {
        std::cout << "\x1b[31mPlease, give output file" << std::endl;
        return 0;
    }

    const auto input = static_cast<std::string>(argv[1]);
    const auto output = static_cast<std::string>(argv[2]);

    if (".bmp" != input.substr(input.size() - 4, 4)) {
        std::cout << "\x1b[31mFormat of your input file is not .bmp, cannot read file" << std::endl;
        return 0;
    }

    if (".bmp" != output.substr(output.size() - 4, 4)) {
        std::cout << "\x1b[31mFormat of your output file is not .bmp, cannot write file" << std::endl;
        return 0;
    }

    FileWorker file_worker;
    Image image = file_worker.ReadIMG(input);
    if (image.GetFileSize() == 0) {
        std::cout << "\x1b[31mSize of your file is 0 (Zero), something went wrong :(" << std::endl;
        return 0;
    }
    for (size_t i = 3; i < argc; ++i) {
        auto filter = static_cast<std::string>(argv[i]);
        if (filter[0] != '-') {
            std::cout << "\x1b[31mThis is not a filter: \x1b[36m" << filter << "\x1b[31m. Maybe you mean \x1b[36m-" << filter << "\x1b[31m? \x1b[0m" << std::endl;
            return 0;
        } else {
            if (filter == "-crop") {
                if (argc - i <= 2) {
                    std::cout << "\x1b[31mPlease give parameters for \x1b[36m-crop\x1b[31m filter\x1b[0m" << std::endl;
                    return 0;
                }

                std::string width_string = static_cast<std::string>(argv[i + 1]);
                std::string height_string = static_cast<std::string>(argv[i + 2]);

                if (!IsStringNumber(width_string) || !IsStringNumber(height_string)) {
                    std::cout << "\x1b[31mParameter is not a number\x1b[0m" << std::endl;
                    return 0;
                }

                int64_t width = std::stoi(width_string);
                int64_t height = std::stoi(height_string);
                i += 2;

                if (width < 0 || height < 0) {
                    std::cout << "\x1b[31mParameter is not a positive integer\x1b[0m" << std::endl;
                    return 0;
                }
                CropFilter crop(width, height);
                crop.Apply(image);
            } else if (filter == "-gs") {
                GrayFilter gray;
                gray.Apply(image);
            } else if (filter == "-neg") {
                NegativeFilter neg;
                neg.Apply(image);
            } else if (filter == "-sharp") {
                SharpFilter sharp;
                sharp.Apply(image);
            } else if (filter == "-edge") {
                if (argc - i <= 1) {
                    std::cout << "\x1b[31mPlease give parameter for \x1b[36m-edge\x1b[31m filter\x1b[0m" << std::endl;
                    return 0;
                }

                std::string threshold_string = static_cast<std::string>(argv[i + 1]);
                i += 1;

                if (!IsStringFloat(threshold_string)) {
                    std::cout << "\x1b[31mPlease give float number for \x1b[36m-edge\x1b[31m filter\x1b[0m" << std::endl;
                    return 0;
                }

                float threshold = std::stof(threshold_string);

                EdgeFilter edge;
                edge.Apply(image, threshold);
            } else if (filter == "-vignette") {
                if (argc - i <= 2) {
                    std::cout << "\x1b[31mPlease give 2 parameters for \x1b[36m-vignette\x1b[31m filter\x1b[0m" << std::endl;
                    return 0;
                }

                std::string radius_string = static_cast<std::string>(argv[i + 1]);
                std::string power_string = static_cast<std::string>(argv[i + 2]);
                i += 2;
                if (!IsStringNumber(radius_string)) {
                    std::cout << "\x1b[31mParameter \x1b[36m" << radius_string << "\x1b[31m is not an integer\x1b[0m" << std::endl;
                    return 0;
                }

                if (!IsStringFloat(power_string)) {
                    std::cout << "\x1b[31mParameter \x1b[36m" << power_string << "\x1b[31m is not a float number\x1b[0m" << std::endl;
                    return 0;
                }

                int64_t diameter = std::stoi(radius_string);
                float power = std::stof(power_string);

                if (diameter <= 0) {
                    std::cout << "\x1b[31mParameter \x1b[36m" << diameter << "\x1b[31m is not a positive integer\x1b[0m" << std::endl;
                    return 0;
                }

                if (diameter >= std::max<size_t>(image.GetWidth(), image.GetHeight())) {
                    std::cout << "\x1b[31mParameter \x1b[36m" << diameter << "\x1b[31m is equal to or greater than image size\x1b[0m" << std::endl;
                    return 0;
                }

                if (power < 0) {
                    std::cout << "\x1b[31mParameter \x1b[36m" << power << "\x1b[31m is less than 0\x1b[0m" << std::endl;
                    return 0;
                }

                VignetteFilter vignette;
                vignette.Apply(image, diameter, power);

            } else if (filter == "-blur") {
                if (argc - i <= 1) {
                    std::cout << "\x1b[31mPlease give parameter for \x1b[36m-blur\x1b[31m filter" << std::endl;
                    return 0;
                }

                std::string sigma_string = static_cast<std::string>(argv[i + 1]);
                i += 1;

                if (!IsStringFloat(sigma_string)) {
                    std::cout << "\x1b[31mParameter \x1b[36m" << sigma_string << "\x1b[31m is not a float\x1b[30m" << std::endl;
                    return 0;
                }

                float sigma = std::stof(sigma_string);

                GaussFilter blur;
                blur.Apply(image, sigma);
            } else {
                std::cout << "\x1b[31mNo such filter \x1b[36m" << filter << std::endl;
                return 0;
            }
        }
    }

    file_worker.ExportIMG(image, output);
    return 0;
}
