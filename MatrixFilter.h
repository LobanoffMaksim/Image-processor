//
// Created by Максим Лобанов on 26.10.2023.
//

#ifndef CPP_HSE_MATRIXFILTER_H
#define CPP_HSE_MATRIXFILTER_H

#include "Filter.h"

#include <vector>

BMPImage::RGB& GetPixel(BMPImage& image, int32_t i, int32_t j);

class MatrixFilter : public Filter {
public:
    ~MatrixFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override {
    }

    void ApplyMatrix(BMPImage& image, const std::vector<std::vector<int32_t>>& matrix);

protected:
    BMPImage::RGB ApplyMatrixForPixel(BMPImage& image, const std::vector<std::vector<int32_t>>& matrix, int32_t i,
                                      int32_t j);
};

#endif  // CPP_HSE_MATRIXFILTER_H
