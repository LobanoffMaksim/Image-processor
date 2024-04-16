#ifndef CPP_HSE_EDGEFILTER_H
#define CPP_HSE_EDGEFILTER_H

#include "Filter.h"

class EdgeFilter : public Filter {
public:
    ~EdgeFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;

protected:
    const std::vector<std::vector<int32_t> > MATRIX_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
};

#endif  // CPP_HSE_EDGEFILTER_H
