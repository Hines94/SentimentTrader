#include "Utils.h"
#include <iostream>
#include <filesystem>
#include <fstream> 
#include <sstream>
#include <chrono> 
#include <ctime> 
#include <iomanip>

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

std::string utils::GetReadableTime()
{
    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();
    
    // Convert to time_t to get a time representation we can format
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure for local timezone
    std::tm localTime;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&localTime, &currentTime); // Windows
#else
    localtime_r(&currentTime, &localTime); // POSIX
#endif

    // Create a string stream to hold the formatted time
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    // Return the formatted string
    return oss.str();
}
