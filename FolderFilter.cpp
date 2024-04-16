#include "FolderFilter.h"
#include "Numbers.h"

#include <algorithm>
#include "cmath"
#include "stdexcept"
#include "iostream"

void FolderFilter::SetBlock(BMPImage& image, BMPImage::RGB& pixel, size_t sx, size_t sy, size_t increase) {

    for (size_t i = sx; i < sx + increase; ++i) {
        for (size_t j = sy; j < sy + increase; ++j) {
            image[i][j] = pixel;
        }
    }
}

void FolderFilter::SetNumber(BMPImage& image, BMPImage* number, size_t sx, size_t sy, size_t increase) {
    for (size_t i = 0; i < number->GetHeight(); ++i) {
        for (size_t j = 0; j < number->GetWidth(); ++j) {
            SetBlock(image, (*number)[i][j], sx + increase * i, sy + increase * j, increase);
        }
    }
}

std::vector<size_t> FolderFilter::DecomposeIntoFigures(size_t x) const {
    std::vector<size_t> answer;
    while (x) {
        answer.push_back(x % FIGURES_COUNT);
        x /= FIGURES_COUNT;
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}

void FolderFilter::AddNumber(BMPImage& image, Numbers& numbers, size_t need_number, size_t sx, size_t sy, size_t fx,
                             size_t fy) {
    std::vector<size_t> figures = DecomposeIntoFigures(need_number);
    size_t need_lendth = 0;
    for (size_t x : figures) {
        need_lendth += numbers.GetNumber(x)->GetWidth();
    }
    need_lendth += numbers.GetNumber(CPP_ID)->GetWidth();
    size_t number_height = (fx - sx) / NUMBER_HIGHT_RATIO;
    number_height += (NUMBER_HEIGHT_BASE - number_height % NUMBER_HEIGHT_BASE) % NUMBER_HEIGHT_BASE;
    size_t increase = number_height / numbers.GetNumber(0)->GetHeight();
    need_lendth *= increase;
    while (need_lendth > fy - sy && increase > 1) {
        need_lendth /= increase;
        number_height /= 2;
        number_height += (NUMBER_HEIGHT_BASE - number_height % NUMBER_HEIGHT_BASE) % NUMBER_HEIGHT_BASE;
        increase = number_height / numbers.GetNumber(0)->GetHeight();
        need_lendth *= increase;
    }
    if (need_lendth > fy - sy) {
        throw std::invalid_argument("To many pieces for such picture.");
    }

    size_t start_x = sx + (fx - sx - number_height) / TITLE_X_INDENT;
    size_t start_y = sy + (fy - sy - need_lendth) / 2;
    for (size_t x : figures) {
        BMPImage* number = numbers.GetNumber(x);
        SetNumber(image, number, start_x, start_y, increase);
        start_y += number->GetWidth() * increase + increase;
    }
    BMPImage* number = numbers.GetNumber(CPP_ID);
    SetNumber(image, number, start_x, start_y, increase);
}

void FolderFilter::SetCornerBorderRadius(BMPImage& image, BMPImage::RGB& pixel, int32_t sx, int32_t sy, int32_t fx,
                                         int32_t fy, int32_t px, int32_t py, int32_t radius) {
    for (size_t x = sx; x < fx; ++x) {
        for (size_t y = sy; y < fy; ++y) {
            if ((x - px) * (x - px) + (y - py) * (y - py) > radius * radius) {
                image[x][y] = pixel;
            }
        }
    }
}

void FolderFilter::SetBorderRadius(BMPImage& image, BMPImage::RGB& pixel, int32_t sx, int32_t sy, int32_t fx,
                                   int32_t fy, int32_t radius) {
    SetCornerBorderRadius(image, pixel, sx, sy, sx + radius, sy + radius, sx + radius, sy + radius, radius);
    SetCornerBorderRadius(image, pixel, sx, fy - radius, sx + radius, fy, sx + radius, fy - radius, radius);
    SetCornerBorderRadius(image, pixel, fx - radius, sy, fx, sy + radius, fx - radius, sy + radius, radius);
    SetCornerBorderRadius(image, pixel, fx - radius, fy - radius, fx, fy, fx - radius, fy - radius, radius);
}

void FolderFilter::ApplyFilter(BMPImage& image, FilterSetting& filter_setting) {
    if (filter_setting.GetParameters().size() != 2) {
        throw std::invalid_argument("Folder filter needs 2 arguments");
    }

    size_t num_x = 0;
    size_t num_y = 0;

    try {
        num_x = static_cast<size_t>(std::stoi(filter_setting.GetParameters()[0]));
        num_y = static_cast<size_t>(std::stoi(filter_setting.GetParameters()[1]));
    } catch (...) {
        throw std::invalid_argument("Arguments for folder filter should be integers >= 0.");
    }
    size_t width = image.GetWidth();
    size_t height = image.GetHeight();
    if (height % num_x != 0) {
        throw std::invalid_argument("Image height should be divided by num_x");
    }
    if (width % num_y != 0) {
        throw std::invalid_argument("Image width should be divided by num_y");
    }
    std::vector<BMPImage::RGBRow> data = image.CopyData();
    std::reverse(data.begin(), data.end());

    size_t block_width = width / num_y;
    size_t block_height = height / num_x;
    size_t addition_x = static_cast<size_t>(static_cast<double>(block_height) * ADDITION_X_RATIO);
    addition_x += addition_x % 2;
    size_t addition_y = static_cast<size_t>(static_cast<double>(addition_x) * ADDITION_Y_RATIO);
    block_height += addition_x;
    block_width += addition_y;

    image.Resize(block_width * num_y + addition_x, block_height * num_x + addition_y);

    BMPImage::RGB white(MAX_COLOR_, MAX_COLOR_, MAX_COLOR_);

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image[i][j] = white;
        }
    }

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            size_t block_i = i / (height / num_x);
            size_t block_j = j / (width / num_y);
            image[i + block_i * addition_x + addition_x][j + block_j * addition_y + addition_y] = data[i][j];
        }
    }
    Numbers numbers;
    for (size_t i = 0; i < num_x; ++i) {
        for (size_t j = 0; j < num_y; ++j) {
            AddNumber(image, numbers, i * num_y + j + 1, addition_x + i * block_height + block_height - addition_x,
                      addition_y + j * block_width, addition_x + (i + 1) * block_height,
                      addition_y + (j + 1) * block_width - addition_y);
        }
    }

    for (size_t block_x = 0; block_x < num_x; ++block_x) {
        for (size_t block_y = 0; block_y < num_y; ++block_y) {
            int32_t radius = static_cast<int32_t>(block_width) / RADIUS_RATIO;
            SetBorderRadius(image, white, static_cast<int32_t>(block_x * block_height + addition_x),
                            static_cast<int32_t>(block_y * block_width + addition_y),
                            static_cast<int32_t>((block_x + 1) * block_height),
                            static_cast<int32_t>((block_y + 1) * block_width), radius);
        }
    }

    image.FlipOver();
}
