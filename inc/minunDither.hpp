#ifndef MINUNDITHER_HPP
#define MINUNDITHER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

 bool hasValidImageExtension(const std::string& filename);
 void generateDither(const std::string& imageFilename);
 
#endif