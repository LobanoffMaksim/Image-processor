#include "GrayscaleFilter.h"

#include <stdexcept>

void GrayscaleFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    if (!filter_setting.GetParameters().empty()) {
        throw std::invalid_argument("GS Filter do not need any parameters.");
    }
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            uint8_t gray_value = static_cast<uint8_t>(RED_RATIO * static_cast<double>(image[i][j].r) +
                                                      GREEN_RATIO * static_cast<double>(image[i][j].g) +
                                                      BLUE_RATIO * static_cast<double>(image[i][j].b));
            image[i][j].r = image[i][j].g = image[i][j].b = gray_value;
        }
    }
}
