#ifndef CPP_HSE_BLURFILTER_H
#define CPP_HSE_BLURFILTER_H

#include "Filter.h"

#include <cmath>

class BlurFilter : public Filter {
public:
    BlurFilter() = default;

    ~BlurFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;

protected:
    void CalcMultiplier(double sigma);

protected:
    std::vector<double> multiplier_;
};

#endif  // CPP_HSE_BLURFILTER_H
