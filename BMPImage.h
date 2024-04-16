#ifndef CPP_HSE_BMPIMAGE_H
#define CPP_HSE_BMPIMAGE_H

#include "algorithm"
#include <cstdint>
#include <string>
#include <fstream>

class BMPImage {
public:
    static const uint16_t BMP_SIGNATURE = 0x4D42;  // BM

    // Предполагаем, что работаем с GCC
    struct BMPHeader {
        uint16_t signature;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    } __attribute__((packed));

    // Предполагаем, что работаем с GCC
    struct DIBHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes_num;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t hor_res;
        int32_t ver_res;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

    struct RGB {
        uint8_t b;
        uint8_t g;
        uint8_t r;

        RGB() = default;

        RGB(uint8_t r, uint8_t g, uint8_t b) : b(b), g(g), r(r) {
        }

    } __attribute__((packed));

    struct RGBRow {

    public:
        RGBRow() = default;

        RGBRow(size_t size, BMPImage* image) : row_(size), image_(image) {
        }

    public:
        /// Read RGBrow. Don't set reading position.
        void ReadRow();

        /// Write RGBrow. Don't set reading position.
        void WriteRow();

        RGB& operator[](size_t i) {
            return row_[i];
        }

        const RGB& operator[](size_t i) const {
            return row_[i];
        }

    protected:
        std::vector<RGB> row_;
        BMPImage* image_;

        friend BMPImage;
    };

public:
    BMPImage() = default;

    BMPImage(BMPImage& image);

    ~BMPImage();

    /// Open file with filename
    /// Automatically close previous file.
    void Open(const std::string& filename);

    /// Close file
    void Close();

    /// Read opened file
    void ReadBmp();

    /// Write image in opened file
    void WriteBmp();

    bool IsOpen() const {
        return file_.is_open();
    }

    const std::string& GetFilename() const {
        return filename_;
    }

    size_t GetHeight() const {
        return static_cast<size_t>(dib_header_.height);
    }

    size_t GetWidth() const {
        return static_cast<size_t>(dib_header_.width);
    }

    RGBRow& operator[](size_t i) {
        return data_[i];
    }

    const RGBRow& operator[](size_t i) const {
        return data_[i];
    }

    // Crops image. m - width, n - height.
    void Crop(size_t m, size_t n);

    void Resize(size_t m, size_t n);

    std::vector<RGBRow> CopyData() {
        return data_;
    }

    void FlipOver() {
        std::reverse(data_.begin(), data_.end());
    }

protected:
    /// Reads BMP header without wetting reading position.
    /// Does not check whether file is open
    void ReadBmpHeader();

    /// Reads BMP dibheader without wetting reading position.
    /// Does not check whether file is open
    void ReadDibHeader();

    /// Reads BMP pixels without wetting reading position.
    /// Does not check whether file is open
    void ReadData();

    //// Writes BMP header without wetting reading position.
    /// Does not check whether file is open
    void WriteBmpHeader();

    /// Reads DIB header without wetting reading position.
    /// Does not check whether file is open
    void WriteDibHeader();

    /// Reads BMP pixels without wetting reading position.
    /// Does not check whether file is open
    void WriteData();

protected:
    std::string filename_;
    std::fstream file_;

    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<RGBRow> data_;

    const uint16_t REQUIRE_BITS_PER_PIXEL = 24;
};

#endif  // CPP_HSE_BMPIMAGE_H
