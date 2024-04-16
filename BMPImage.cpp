#include "BMPImage.h"

#include <algorithm>

BMPImage::~BMPImage() {
    try {
        Close();
    } catch (std::runtime_error &e) {
        throw e;
    }
}

void BMPImage::Open(const std::string &filename) {
    if (file_.is_open()) {
        Close();
    }

    if (filename.empty()) {
        throw std::invalid_argument("Filename is empty.");
    }

    filename_ = filename;
    try {
        file_.open(filename_);
    } catch (...) {

        std::string error_message = "Cannot open file ";
        error_message += filename_;
        throw std::runtime_error(error_message);
    }
    if (!file_.is_open()) {

        std::string error_message = "Cannot open file ";
        error_message += filename_;
        throw std::runtime_error(error_message);
    }
}

void BMPImage::Close() {
    try {
        file_.close();
    } catch (...) {
        throw std::runtime_error("Can bot close file.");
    }
    filename_.clear();
}

void BMPImage::ReadBmp() {
    if (!IsOpen()) {
        throw std::logic_error("File is not open.");
    }

    // Always read from the beginning
    file_.seekg(0);
    try {
        ReadBmpHeader();
        ReadDibHeader();
        ReadData();
    } catch (std::runtime_error &e) {
        throw e;
    }
}

void BMPImage::ReadBmpHeader() {
    if (!file_) {
        throw std::runtime_error("BMP File is not correct.");
    }
    file_.read(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));
    if (!file_) {
        throw std::runtime_error("Can not read BMP header");
    }

    // Checking the correctness of the bmp header
    if (bmp_header_.signature != BMP_SIGNATURE) {
        throw std::runtime_error("BMP File is not correct.");
    }
}

void BMPImage::ReadDibHeader() {
    if (!file_) {
        throw std::runtime_error("BMP File is not correct.");
    }
    file_.read(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
    if (!file_) {
        throw std::runtime_error("Can not read DIB header");
    }

    if (dib_header_.bits_per_pixel != REQUIRE_BITS_PER_PIXEL) {
        throw std::runtime_error("DIB Header bits_per_pixel must be 24.");
    }
}

void BMPImage::ReadData() {
    file_.seekg(bmp_header_.offset - static_cast<int32_t>(sizeof(BMPHeader) + sizeof(DIBHeader)), std::ios::cur);
    for (size_t i = 0; i < dib_header_.height; ++i) {
        data_.push_back(RGBRow(dib_header_.width, this));
        try {
            data_.back().ReadRow();
        } catch (std::runtime_error &e) {
            throw e;
        }
    }
}

void BMPImage::RGBRow::ReadRow() {
    for (size_t i = 0; i < row_.size(); ++i) {
        try {
            image_->file_.read(reinterpret_cast<char *>(&row_[i]), sizeof(RGB));
        } catch (...) {
            throw std::runtime_error("Can not read pixels.");
        }
    }
    int32_t extra_bytes = ((3 * image_->dib_header_.width + 3) / 4) * 4 - image_->dib_header_.width * 3;
    try {
        image_->file_.seekg(extra_bytes, std::ios::cur);
    } catch (...) {
        throw std::runtime_error("Can not skip extra pixels.");
    }
}

void BMPImage::WriteBmp() {
    if (!IsOpen()) {
        throw std::logic_error("File is not open.");
    }

    file_.seekg(0);
    try {
        WriteBmpHeader();
        WriteDibHeader();
        WriteData();
    } catch (std::runtime_error &e) {
        throw e;
    }
}

void BMPImage::WriteBmpHeader() {
    bmp_header_.offset = sizeof(DIBHeader) + sizeof(BMPHeader);
    size_t extra_bytes = ((3 * dib_header_.width + 3) / 4) * 4;
    bmp_header_.size = sizeof(DIBHeader) + sizeof(BMPHeader) + dib_header_.height * (extra_bytes);
    try {
        file_.write(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));
    } catch (...) {
        throw std::runtime_error("Can't write Bmp Header.");
    }
}

void BMPImage::WriteDibHeader() {
    dib_header_.header_size = sizeof(DIBHeader);
    dib_header_.image_size = dib_header_.width * dib_header_.height;
    try {
        file_.write(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
    } catch (...) {
        throw std::runtime_error("Can't write DIB Header.");
    }
}

void BMPImage::WriteData() {
    for (size_t i = 0; i < dib_header_.height; ++i) {
        try {
            data_[i].WriteRow();
        } catch (std::runtime_error &e) {
            throw e;
        }
    }
}

void BMPImage::RGBRow::WriteRow() {
    for (size_t j = 0; j < row_.size(); ++j) {
        uint8_t buffer[3] = {row_[j].b, row_[j].g, row_[j].r};
        try {
            image_->file_.write(reinterpret_cast<char *>(&buffer), sizeof(RGB));
        } catch (...) {
            throw std::runtime_error("Can not write row");
        }
    }

    size_t extra_bytes = ((3 * row_.size() + 3) / 4) * 4 - row_.size() * 3;
    char extra_zeros[] = {0, 0, 0};
    try {
        image_->file_.write(extra_zeros, static_cast<std::streamsize>(extra_bytes));
    } catch (...) {
        throw std::runtime_error("Can not write extra zeros");
    }
}

void BMPImage::Crop(size_t m, size_t n) {
    std::reverse(data_.begin(), data_.end());
    if (dib_header_.height > static_cast<int32_t>(n)) {
        data_.resize(n);
        dib_header_.height = static_cast<int32_t>(n);
    }
    for (size_t i = 0; i < n; ++i) {
        if (dib_header_.width > static_cast<int32_t>(m)) {
            data_[i].row_.resize(m);
        }
    }
    dib_header_.width = std::min(dib_header_.width, static_cast<int32_t>(m));
    std::reverse(data_.begin(), data_.end());
}

void BMPImage::Resize(size_t m, size_t n) {

    data_.resize(n);
    dib_header_.height = static_cast<int32_t>(n);

    for (size_t i = 0; i < n; ++i) {

        data_[i].row_.resize(m);
        data_[i].image_ = this;
    }
    dib_header_.width = static_cast<int32_t>(m);
}

BMPImage::BMPImage(BMPImage &image) {
    filename_ = image.filename_;

    bmp_header_ = image.bmp_header_;
    dib_header_ = image.dib_header_;
    data_.resize(dib_header_.height);
    for (size_t i = 0; i < image.dib_header_.height; ++i) {
        data_[i].image_ = this;
        data_[i].row_ = image.data_[i].row_;
    }
}
