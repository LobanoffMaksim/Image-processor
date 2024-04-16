#ifndef CPP_HSE_CROPFILTER_H
#define CPP_HSE_CROPFILTER_H

#include "Filter.h"

class CropFilter : public Filter {
public:
    ~CropFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;
};

#endif  // CPP_HSE_CROPFILTER_H
