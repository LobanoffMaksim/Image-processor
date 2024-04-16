#include "CropFilter.h"

#include <stdexcept>
#include <string>

void CropFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    if (filter_setting.GetParameters().size() != 2) {
        throw std::invalid_argument("Crop Filter requires 2 arguments.");
    }
    size_t width = 0;
    size_t height = 0;
    try {
        width = static_cast<size_t>(std::stoi(filter_setting.GetParameters()[0]));
        height = static_cast<size_t>(std::stoi(filter_setting.GetParameters()[1]));
    } catch (...) {
        throw std::invalid_argument("Arguments should be integers >= 0.");
    }

    image.Crop(width, height);
}
