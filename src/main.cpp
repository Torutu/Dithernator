#include "../inc/minunDither.hpp"

int main(int argc, char** argv) {
    // Check if an image filename is provided as a command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<image_filename>" << std::endl;
        return -1;
    }

    std::string imageFilename = argv[1];

    if (!hasValidImageExtension(imageFilename)) {
        std::cerr << "Error: The file must be a valid image!" << std::endl;
        return -1;
    }

    // Dithers the image using Floyd-Steinberg algorithm
    generateDither(imageFilename);

    return 0;
}