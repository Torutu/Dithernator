extern "C"{
    #define STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #define STBI_NO_THREAD_LOCALS  //Fix TLS errors in MinGW
    #include "../inc/stb_image.h"
    #include "../inc/stb_image_write.h"
}

#include <iostream>
#include <vector>
#include <string>
#include "../inc/minunDither.hpp"

bool hasValidImageExtension(const std::string& filename) {
    static const std::vector<std::string> validExtensions = {
        ".jpg", ".jpeg", ".png", ".bmp"
    };

    for (const auto& ext : validExtensions) {
        if (filename.size() > ext.size() && filename.substr(filename.size() - ext.size()) == ext) {
            return true;
        }
    }
    return false;
}

// Floyd-Steinberg Dithering, Bill Atiknson variant
void floydSteinbergDither(unsigned char* image, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            int oldPixel = image[index];
            int newPixel = (oldPixel > 128) ? 255 : 0;
            int quantError = oldPixel - newPixel;
            //std::cout << "Quant Error = oldPixel - newPixel = \n" << quantError << " = " << oldPixel << " - " << newPixel << std::endl; debug
            image[index] = newPixel;

            // Distribute error to neighboring pixels
            if (x + 1 < width) {
                int indexRight = (y * width + (x + 1)) * channels;
                image[indexRight] += quantError * 1 / 12;
            }
            if (x + 2 < width) {
                int indexRight2 = (y * width + (x + 2)) * channels;
                image[indexRight2] += quantError * 1 / 12;
            }
            if (y + 1 < height) {
                if (x > 0) {
                    int indexBottomLeft = ((y + 1) * width + (x - 1)) * channels;
                    image[indexBottomLeft] += quantError * 1 / 12;
                }
                int indexBottom = ((y + 1) * width + x) * channels;
                image[indexBottom] += quantError * 1 / 12;
                if (x + 1 < width) {
                    int indexBottomRight = ((y + 1) * width + (x + 1)) * channels;
                    image[indexBottomRight] += quantError * 1 / 12;
                }
            }
            if (y + 2 < height) {
                int indexBottom2 = ((y + 2) * width + x) * channels;
                image[indexBottom2] += quantError * 1 / 12;
            }
        }
    }
}

void generateDither(const std::string& imageFilename) {
    int width, height, channels;
    unsigned char* image = stbi_load(imageFilename.c_str(), &width, &height, &channels, 1);
    
    if (!image) {
        std::cerr << "Error: Unable to load image " << imageFilename << std::endl;
        return;
    }

    floydSteinbergDither(image, width, height, 1);
    // Extract directory from imageFilename
    std::filesystem::path imagePath(imageFilename);
    std::string directory = imagePath.parent_path().string(); // Get parent directory
    std::string filename = "Dithered_" + imagePath.filename().string(); // Modify filename
    // Combine directory + new filename
    std::string imageFilenameOut = directory.empty() ? filename : directory + "/" + filename;
    stbi_write_jpg(imageFilenameOut.c_str(), width, height, 1, image, 100);
    std::cout << "Dithering applied, saved as " << imageFilenameOut << std::endl;

    stbi_image_free(image);
}
