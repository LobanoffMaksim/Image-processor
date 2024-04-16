#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H

#include "BMPImage.h"
#include "CmdLineParser.h"

class Filter {
public:
    Filter() = default;

    virtual void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    }

    virtual ~Filter() = default;

protected:
    const uint8_t MAX_COLOR_ = 255;
};

#endif  // CPP_HSE_FILTER_H
