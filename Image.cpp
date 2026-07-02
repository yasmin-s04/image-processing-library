//Image.cpp

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

// Default constructor
Image::Image() : Matrix(), filePath(""), numChannels(0), width(0), height(0) {}

// Load image constructor
Image::Image(const std::string& filePath) {
    int w, h, channels;
    uint8_t* img = stbi_load(filePath.c_str(), &w, &h, &channels, 0);
    if (!img) throw std::runtime_error("Failed to load image");

    this->filePath = filePath;
    this->numChannels = channels;
    this->width = w;
    this->height = h;

    // Initialize the matrix with proper dimensions
    data = Vector<Vector<uint8_t>>(h);
    for (int i = 0; i < h; ++i) {
        data[i] = Vector<uint8_t>(w * channels);
        for (int j = 0; j < w * channels; ++j) {
            data[i][j] = img[i * w * channels + j];
        }
    }

    stbi_image_free(img);
}

// Param constructor
Image::Image(const std::string& filePath, int numChannels, int width, int height)
    : Matrix(height, width * numChannels),
      filePath(filePath), numChannels(numChannels), width(width), height(height) {}

// Copy constructor
Image::Image(const Image& other)
    : Matrix(other), filePath(other.filePath), numChannels(other.numChannels),
      width(other.width), height(other.height) {}

// Assignment operator
Image& Image::operator=(const Image& other) {
    if (this != &other) {
        Matrix::operator=(other);
        filePath = other.filePath;
        numChannels = other.numChannels;
        width = other.width;
        height = other.height;
    }
    return *this;
}

// Destructor
Image::~Image() {}

// Scaling by scalar
Image Image::operator*(double scalar) const {
    Image result = *this;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width * numChannels; ++j)
            result[i][j] = std::clamp(static_cast<int>(data[i][j] * scalar), 0, 255);
    return result;
}

// Add
Image Image::operator+(const Image& other) const {
    if (width != other.width || height != other.height || numChannels != other.numChannels)
        throw std::invalid_argument("Image dimensions/channels must match");

    Image result = *this;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width * numChannels; ++j)
            result[i][j] = std::clamp(static_cast<int>(data[i][j] + other[i][j]), 0, 255);
    return result;
}

// Subtract
Image Image::operator-(const Image& other) const {
    if (width != other.width || height != other.height || numChannels != other.numChannels)
        throw std::invalid_argument("Image dimensions/channels must match");

    Image result = *this;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width * numChannels; ++j)
            result[i][j] = std::clamp(static_cast<int>(data[i][j] - other[i][j]), 0, 255);
    return result;
}

// Multiply (pixel-wise)
Image Image::operator*(const Image& other) const {
    if (width != other.width || height != other.height || numChannels != other.numChannels)
        throw std::invalid_argument("Image dimensions/channels must match");

    Image result = *this;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width * numChannels; ++j)
            result[i][j] = std::clamp(static_cast<int>((data[i][j] * other[i][j]) / 255.0), 0, 255);
    return result;
}

// Resize using stb_image_resize
void Image::resize(int newWidth, int newHeight) {
    std::vector<uint8_t> originalData;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width * numChannels; ++j)
            originalData.push_back(data[i][j]);

    std::vector<uint8_t> resizedData(newWidth * newHeight * numChannels);

    // Use stb_image_resize
    stbir_resize_uint8(
        originalData.data(), width, height, 0,
        resizedData.data(), newWidth, newHeight, 0,
        numChannels
    );

    width = newWidth;
    height = newHeight;

    data = Vector<Vector<uint8_t>>(height);
    for (int i = 0; i < height; ++i) {
        data[i] = Vector<uint8_t>(width * numChannels);
        for (int j = 0; j < width * numChannels; ++j) {
            data[i][j] = resizedData[i * width * numChannels + j];
        }
    }
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::save(const std::string& filePath) const {
    std::vector<uint8_t> imageData;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * numChannels; ++j) {
            imageData.push_back(data[i][j]);
        }
    }

    stbi_write_png(filePath.c_str(), width, height, numChannels, imageData.data(), width * numChannels);
}




