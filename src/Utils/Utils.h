#include <string>


class utils {
public:
    static bool CreateDirectory(std::string loc);

    static void saveDataToFile(std::string fileLoc,std::string Data);
};