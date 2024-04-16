#ifndef CPP_HSE_SHARPFILTER_H
#define CPP_HSE_SHARPFILTER_H

#include "Filter.h"

#include <vector>

class SharpFilter : public Filter {
public:
    ~SharpFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;

protected:
    const std::vector<std::vector<int32_t> > MATRIX_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};

#endif  // CPP_HSE_SHARPFILTER_H
