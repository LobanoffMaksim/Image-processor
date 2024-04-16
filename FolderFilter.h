#ifndef CPP_HSE_FOLDERFILTER_H
#define CPP_HSE_FOLDERFILTER_H

#include "Filter.h"
#include "Numbers.h"

class FolderFilter : public Filter {
public:
    ~FolderFilter() override = default;

public:
    void ApplyFilter(BMPImage& image, FilterSetting& filter_setting) override;

protected:
    void SetBlock(BMPImage& image, BMPImage::RGB& pixel, size_t sx, size_t sy, size_t increase);

    void SetNumber(BMPImage& image, BMPImage* number, size_t sx, size_t sy, size_t increase);

    std::vector<size_t> DecomposeIntoFigures(size_t x) const;

    void AddNumber(BMPImage& image, Numbers& numbers, size_t need_number, size_t sx, size_t sy, size_t fx, size_t fy);

    void SetCornerBorderRadius(BMPImage& image, BMPImage::RGB& pixel, int32_t sx, int32_t sy, int32_t fx, int32_t fy,
                               int32_t px, int32_t py, int32_t radius);

    void SetBorderRadius(BMPImage& image, BMPImage::RGB& pixel, int32_t sx, int32_t sy, int32_t fx, int32_t fy,
                         int32_t radius);

protected:
    const size_t FIGURES_COUNT = 10;
    const size_t CPP_ID = 10;
    const size_t NUMBER_HIGHT_RATIO = 4;
    const size_t NUMBER_HEIGHT_BASE = 5;
    const size_t TITLE_X_INDENT = 3;
    const double ADDITION_X_RATIO = 0.5;
    const double ADDITION_Y_RATIO = 1;
    const int32_t RADIUS_RATIO = 20;
};

#endif  // CPP_HSE_FOLDERFILTER_H
