#include "BMPImage.h"
#include "EdgeFilter.h"
#include "MatrixFilter.h"
#include "GrayscaleFilter.h"

#include <stdexcept>
#include <string>

void EdgeFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    if (filter_setting.GetParameters().size() != 1) {
        throw std::invalid_argument("Edge filter requires 1 parameter.");
    }
    double theshold = 0;

    try {
        theshold = static_cast<double>(std::stod(filter_setting.GetParameters()[0]));
    } catch (...) {
        throw std::invalid_argument("Theshold must be double.");
    }
    if (theshold < 0 || theshold > 1) {
        throw std::invalid_argument("Theshold must be in [0...1].");
    }

    GrayscaleFilter gs_filter;
    FilterSetting gs_filter_setting("-gs");
    gs_filter.ApplyFilter(image, gs_filter_setting);

    MatrixFilter matrix_filter;
    matrix_filter.ApplyMatrix(image, MATRIX_);
    BMPImage::RGB white(MAX_COLOR_, MAX_COLOR_, MAX_COLOR_);
    BMPImage::RGB black(0, 0, 0);
    uint8_t max_allowed_color = static_cast<uint8_t>(static_cast<double>(MAX_COLOR_) * theshold);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            if (image[i][j].r > max_allowed_color) {
                image[i][j] = white;
            } else {
                image[i][j] = black;
            }
        }
    }
}
