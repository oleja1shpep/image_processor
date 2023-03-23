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
        std::cout << "\n\nImage Processor\n\n"
                     "Simple console app to apply filters on your photos\n"
                     "<IMPORTANT: images should be 24-bit .bmp files>\n\n"
                     "Usage:\n"
                     "     ./image_processor input.bmp output.bmp -[filter1] {arg1_1} {agr1_2}...-[filter2] {arg2_1} {arg2_2} ...\n"
                     "\nExample:\n"
                     "     ./image_processor input.bmp output.bmp -gs -blur 4 -edge 0.1 -crop 1000 1000\n"
                     "\n<IMPORTANT: you can use relative paths from /build or absolute paths>\n\n"
                     "Commands:\n"
                     "    -neg                        |  Negative filter\n"
                     "    -gs                         |  Grayscale filter\n"
                     "    -sharp                      |  Sharpening filter\n"
                     "    -edge <threshold>           |  Edge detection filter\n"
                     "    -crop <width, height>       |  Crop filter\n"
                     "    -blur <sigma>               |  Gauss blur filter(takes a little bit too long)\n"
                     "    -vignette <diameter, power> |  Vignette filter\n\n"
                  << std::endl;
        return 0;
    }

    if (argc == 2) {
        std::cout << "Please, give output file" << std::endl;
        return 0;
    }

    const auto input = static_cast<std::string>(argv[1]);
    const auto output = static_cast<std::string>(argv[2]);

    if (".bmp" != input.substr(input.size() - 4, 4)) {
        std::cout << "Format of your input file is not .bmp, cannot read file" << std::endl;
        return 0;
    }

    if (".bmp" != output.substr(output.size() - 4, 4)) {
        std::cout << "Format of your output file is not .bmp, cannot write file" << std::endl;
        return 0;
    }

    FileWorker file_worker;
    Image image = file_worker.ReadIMG(input);
    if (image.GetFileSize() == 0) {
        std::cout << "Size of your file is 0 (Zero), something went wrong :(" << std::endl;
        return 0;
    }
    for (size_t i = 3; i < argc; ++i) {
        auto filter = static_cast<std::string>(argv[i]);
        if (filter[0] != '-') {
            std::cout << "this is not a filter: " << filter << ". Maybe you mean -" << filter << "?" << std::endl;
            return 0;
        } else {
            if (filter == "-crop") {
                if (argc - i <= 2) {
                    std::cout << "please give parameters for -crop filter" << std::endl;
                    return 0;
                }

                std::string width_string = static_cast<std::string>(argv[i + 1]);
                std::string height_string = static_cast<std::string>(argv[i + 2]);

                if (!IsStringNumber(width_string) || !IsStringNumber(height_string)) {
                    std::cout << "parameter is not a number" << std::endl;
                    return 0;
                }

                int64_t width = std::stoi(width_string);
                int64_t height = std::stoi(height_string);
                i += 2;

                if (width < 0 || height < 0) {
                    std::cout << "parameter is not a positive integer" << std::endl;
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
                    std::cout << "please give parameter for -edge filter" << std::endl;
                    return 0;
                }

                std::string threshold_string = static_cast<std::string>(argv[i + 1]);
                i += 1;

                if (!IsStringFloat(threshold_string)) {
                    std::cout << "please give float number for -edge filter" << std::endl;
                    return 0;
                }

                float threshold = std::stof(threshold_string);

                EdgeFilter edge;
                edge.Apply(image, threshold);
            } else if (filter == "-vignette") {
                if (argc - i <= 2) {
                    std::cout << "please give 2 parameters for -vignette filter" << std::endl;
                    return 0;
                }

                std::string radius_string = static_cast<std::string>(argv[i + 1]);
                std::string power_string = static_cast<std::string>(argv[i + 2]);
                i += 2;
                if (!IsStringNumber(radius_string)) {
                    std::cout << "parameter " << radius_string << " is not an integer" << std::endl;
                    return 0;
                }

                if (!IsStringFloat(power_string)) {
                    std::cout << "parameter " << power_string << " is not a float number" << std::endl;
                    return 0;
                }

                int64_t diameter = std::stoi(radius_string);
                float power = std::stof(power_string);

                if (diameter <= 0) {
                    std::cout << "parameter " << diameter << " is not a positive integer" << std::endl;
                    return 0;
                }

                if (diameter >= std::max<size_t>(image.GetWidth(), image.GetHeight())) {
                    std::cout << "parameter " << diameter << " is equal to or greater than image size" << std::endl;
                    return 0;
                }

                if (power < 0) {
                    std::cout << "parameter " << power << " is less than 0" << std::endl;
                    return 0;
                }

                VignetteFilter vignette;
                vignette.Apply(image, diameter, power);

            } else if (filter == "-blur") {
                if (argc - i <= 1) {
                    std::cout << "please give parameter for -blur filter" << std::endl;
                    return 0;
                }

                std::string sigma_string = static_cast<std::string>(argv[i + 1]);
                i += 1;

                if (!IsStringFloat(sigma_string)) {
                    std::cout << "parameter " << sigma_string << " is not a float" << std::endl;
                    return 0;
                }

                float sigma = std::stof(sigma_string);

                GaussFilter blur;
                blur.Apply(image, sigma);
            } else {
                std::cout << "no such filter " << filter << std::endl;
                return 0;
            }
        }
    }

    file_worker.ExportIMG(image, output);
    return 0;
}
