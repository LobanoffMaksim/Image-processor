#include "CmdLineParser.h"

CmdLineParser::CmdLineParser(int argc, char **argv) {
    if (argc == 1) {
        throw std::invalid_argument(
            "Instruction:\n"
            "Supported files: BMP 24-bits\n"
            "Order of arguments: {programme name} {input path} {output path} [-{name of first filter}, {parameters of "
            "first filter}] [-{name of second filter}, {parameters of second filter}] ...\n"
            "Filters:\n"
            "Сrop (-crop width height)\n"
            "Edge Detection (-edge threshold), example -edge 0.1\n"
            "Sharpening (-sharp)\n"
            "Negative (-neg)\n"
            "Grayscale (-gs)\n"
            "Gaussian Blur (-blur sigma), example -blur 7.5\n"
            "Folder view (-folder number_x number_y), example -folder 8 4\n"
            "Example: lenna.bmp output.bmp -crop 500 500 -neg -blur -gs -crop 100 500\n"
            "!!! There may be problems with folder filter, because relative path for Numbers.h "
            "specified for correct operation in the testing system");
    }
    if (argc < 3) {
        throw std::invalid_argument("Not enough arguments.");
    }
    input_file_ = argv[1];
    output_file_ = argv[2];

    if (input_file_.size() < 4 || input_file_.substr(input_file_.size() - 4) != ".bmp") {
        throw std::invalid_argument("Input file should be .bmp format.");
    }
    if (output_file_.size() < 4 || output_file_.substr(output_file_.size() - 4) != ".bmp") {
        throw std::invalid_argument("Input file should be .bmp format.");
    }

    for (size_t i = 3; i < argc; ++i) {
        if (argv[i][0] != '-') {
            if (filters_.empty()) {
                throw std::invalid_argument("Filter parameter without filter.");
            } else {
                filters_.back().AddParameter(argv[i]);
            }
        } else {
            filters_.push_back(FilterSetting(argv[i]));
        }
    }
}
