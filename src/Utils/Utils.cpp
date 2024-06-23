#include "Utils.h"
#include <iostream>
#include <filesystem>
#include <fstream> 

namespace fs = std::filesystem;

bool utils::CreateDirectory(std::string directory)
{
    if (!fs::exists(directory)) {
        if (fs::create_directory(directory)) {
            std::cout << "Directory created: " << directory << std::endl;
            return true;
        } else {
            std::cerr << "Failed to create directory: " << directory << std::endl;
            return false;
        }
    } else {
        std::cout << "Directory already exists: " << directory << std::endl;
        return true;
    }
}

void utils::saveDataToFile(std::string fileName, std::string Data)
{
    // Create an output file stream object
    std::ofstream outfile(fileName);

    // Check if the file stream is open
    if (outfile.is_open()) {
        // Write text to the file
        outfile << Data;

        // Close the file stream
        outfile.close();

        std::cout << "News saved to file: " << fileName << std::endl;
    } else {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
}
