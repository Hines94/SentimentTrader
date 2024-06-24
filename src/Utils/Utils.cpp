#include "Utils.h"
#include <iostream>
#include <filesystem>
#include <fstream> 
#include <sstream>

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

void utils::SaveDataToFile(std::string fileName, std::string Data)
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

std::string utils::LoadDataFromFile(std::string fileLoc)
{
    std::ifstream file(fileLoc); // Create an input file stream

    // Check if the file stream is open
    if (!file.is_open()) {
        std::cerr << "File not found or could not be opened: " << fileLoc << std::endl;
        return ""; // Return an empty string if the file doesn't exist or can't be opened
    }

    // Use a string stream to read the file contents into a string
    std::ostringstream ss;
    ss << file.rdbuf(); // Read the file contents into the string stream

    return ss.str(); // Return the string containing the file contents
}
