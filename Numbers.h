#ifndef CPP_HSE_NUMBERS_H
#define CPP_HSE_NUMBERS_H

#include "BMPImage.h"

#include <vector>
#include <string>

class Numbers {
public:
    Numbers();

    ~Numbers();

public:
    BMPImage* GetNumber(size_t x) {
        return numbers_[x];
    }

protected:
    std::vector<BMPImage*> numbers_;
    std::string filepath_ =
        "/Users/maksimlobanov/se/pmi-235-1-Maks-Lobanoff-mlobanov/tasks/image_processor/Numbers/0.bmp";
    const std::vector<char> symbols = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'c'};
    const size_t FILE_NAME_ID = 5;
};

#endif  // CPP_HSE_NUMBERS_H
