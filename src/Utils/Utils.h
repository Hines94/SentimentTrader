#include <string>


class utils {
public:
    static bool CreateDirectory(std::string loc);

    static void SaveDataToFile(std::string fileLoc,std::string Data);

    static std::string LoadDataFromFile(std::string fileLoc);

    static bool fileExists(std::string fileLoc);

    static std::string GetReadableTime();
};