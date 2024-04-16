

#ifndef CPP_HSE_NEGFILTER_H
#define CPP_HSE_NEGFILTER_H

#include "Filter.h"

class NegFilter : public Filter {
public:
    ~NegFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;
};

#endif  // CPP_HSE_NEGFILTER_H
