#include "MatrixFilter.h"
#include "BMPImage.h"

#include <algorithm>
#include <stdexcept>

BMPImage::RGB& GetPixel(BMPImage& image, int32_t i, int32_t j) {
    i = std::max(i, static_cast<int32_t>(0));
    j = std::max(j, static_cast<int32_t>(0));
    i = std::min(i, static_cast<int32_t>(image.GetHeight()) - 1);
    j = std::min(j, static_cast<int32_t>(image.GetWidth()) - 1);
    return image[i][j];
}

BMPImage::RGB MatrixFilter::ApplyMatrixForPixel(BMPImage& image, const std::vector<std::vector<int32_t>>& matrix,
                                                int32_t i, int32_t j) {
    int32_t step = static_cast<int32_t>(matrix.size()) / 2;
    int32_t r = 0;
    int32_t g = 0;
    int32_t b = 0;
    for (int32_t id_i = i - step; id_i <= i + step; ++id_i) {
        for (int32_t id_j = j - step; id_j <= j + step; ++id_j) {
            int32_t value = matrix[id_i - (i - step)][id_j - (j - step)];
            r += value * GetPixel(image, id_i, id_j).r;
            g += value * GetPixel(image, id_i, id_j).g;
            b += value * GetPixel(image, id_i, id_j).b;
        }
    }
    r = std::max(static_cast<int32_t>(0), std::min(static_cast<int32_t>(MAX_COLOR_), r));
    g = std::max(static_cast<int32_t>(0), std::min(static_cast<int32_t>(MAX_COLOR_), g));
    b = std::max(static_cast<int32_t>(0), std::min(static_cast<int32_t>(MAX_COLOR_), b));

    BMPImage::RGB pixel(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
    return pixel;
}

void MatrixFilter::ApplyMatrix(BMPImage& image, const std::vector<std::vector<int32_t>>& matrix) {
    if (matrix.size() % 2 != 1 || matrix.size() != matrix[0].size()) {
        throw std::invalid_argument("Invalid matrix.");
    }

    std::vector<std::vector<BMPImage::RGB>> data(image.GetHeight(), std::vector<BMPImage::RGB>(image.GetWidth()));

    for (int32_t i = 0; i < static_cast<int32_t>(image.GetHeight()); ++i) {
        for (int32_t j = 0; j < static_cast<int32_t>(image.GetWidth()); ++j) {
            data[i][j] = ApplyMatrixForPixel(image, matrix, i, j);
        }
    }
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image[i][j] = data[i][j];
        }
    }
}
