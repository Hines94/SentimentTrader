#include <string>
#include <map>

class EnvManager {
public:
    static EnvManager& getInstance() {
        static EnvManager instance;
        return instance;
    }

    std::string getParam(std::string paramName);
    bool getBoolParam(std::string paramName);
    int getIntParam(std::string paramName);


    EnvManager(EnvManager const&) = delete;
    void operator=(EnvManager const&) = delete;

private:
    EnvManager();
    std::map<std::string,std::string> envVars;
};