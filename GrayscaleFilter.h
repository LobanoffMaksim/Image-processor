#ifndef CPP_HSE_GRAYSCALEFILTER_H
#define CPP_HSE_GRAYSCALEFILTER_H

#include "Filter.h"

class GrayscaleFilter : public Filter {
public:
    ~GrayscaleFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;

protected:
    const double RED_RATIO = 0.299;
    const double GREEN_RATIO = 0.587;
    const double BLUE_RATIO = 0.114;
};

#endif  // CPP_HSE_GRAYSCALEFILTER_H
