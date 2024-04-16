#include "Numbers.h"

#include <stdexcept>

Numbers::Numbers() {

    for (char number : symbols) {

        try {
            filepath_[filepath_.size() - FILE_NAME_ID] = number;
            BMPImage* image = new BMPImage();
            image->Open(filepath_);
            image->ReadBmp();
            image->FlipOver();
            numbers_.push_back(image);

        } catch (...) {
            throw std::runtime_error("Can not open file.");
        }
    }
}

Numbers::~Numbers() {
    for (BMPImage* image_pointer : numbers_) {
        delete image_pointer;
    }
}
