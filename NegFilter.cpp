#include "NegFilter.h"

#include "stdexcept"

void NegFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    if (!filter_setting.GetParameters().empty()) {
        throw std::invalid_argument("Negative filter do not need any parameters.");
    }

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image[i][j].r = MAX_COLOR_ - image[i][j].r;
            image[i][j].g = MAX_COLOR_ - image[i][j].g;
            image[i][j].b = MAX_COLOR_ - image[i][j].b;
        }
    }
}
