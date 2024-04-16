#include "MatrixFilter.h"
#include "SharpFilter.h"

#include "stdexcept"

void SharpFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    try {
        MatrixFilter matrix_filter;
        matrix_filter.ApplyMatrix(image, MATRIX_);
    } catch (std::invalid_argument& e) {
        throw e;
    }
}
