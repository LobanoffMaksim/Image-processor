#include "BlurFilter.h"
#include "MatrixFilter.h"

void BlurFilter::CalcMultiplier(double sigma) {
    int32_t step = static_cast<int32_t>(sigma * 3) + 1;
    multiplier_.resize(step);
    for (int32_t x = 0; x < step; ++x) {
        multiplier_[x] =
            std::exp(-static_cast<double>(x * x) / sigma / sigma / 2) / std::sqrt(sigma * sigma * 2 * M_PI);
    }
}

void BlurFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    double sigma = 0;

    try {
        sigma = static_cast<double>(std::stod(filter_setting.GetParameters()[0]));
    } catch (...) {
        throw std::invalid_argument("For Blur filter sigma must be double.");
    }
    if (sigma <= 0) {
        throw std::invalid_argument("For Blur filter sigma must be positive.");
    }
    CalcMultiplier(sigma);
    int32_t step = static_cast<int32_t>(sigma * 3) + 1;
    std::vector<std::vector<BMPImage::RGB> > new_data(image.GetHeight(), std::vector<BMPImage::RGB>(image.GetWidth()));
    for (int32_t j = 0; j < image.GetWidth(); ++j) {
        std::vector<double> r(image.GetHeight(), 0.0);
        std::vector<double> g(image.GetHeight(), 0.0);
        std::vector<double> b(image.GetHeight(), 0.0);
        for (int i = 0; i < static_cast<int>(image.GetHeight()); ++i) {
            for (int y = j - step + 1; y < j + step; ++y) {
                BMPImage::RGB pixel = GetPixel(image, i, y);
                r[i] += static_cast<double>(pixel.r) * multiplier_[abs(y - j)];
                g[i] += static_cast<double>(pixel.g) * multiplier_[abs(y - j)];
                b[i] += static_cast<double>(pixel.b) * multiplier_[abs(y - j)];
            }
        }
        for (int i = 0; i < static_cast<int>(image.GetHeight()); ++i) {
            double r2 = 0.0;
            double g2 = 0.0;
            double b2 = 0.0;
            for (int x = i - step + 1; x < i + step; ++x) {
                int32_t ind = std::min(static_cast<int32_t>(image.GetHeight() - 1), std::max(0, x));
                r2 += r[ind] * multiplier_[abs(x - i)];
                g2 += g[ind] * multiplier_[abs(x - i)];
                b2 += b[ind] * multiplier_[abs(x - i)];
            }
            new_data[i][j].r = static_cast<uint8_t>(r2);
            new_data[i][j].g = static_cast<uint8_t>(g2);
            new_data[i][j].b = static_cast<uint8_t>(b2);
        }
    }
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image[i][j] = new_data[i][j];
        }
    }

    multiplier_.clear();
}
