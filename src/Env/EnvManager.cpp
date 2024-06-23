#include "EnvManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unistd.h>

using namespace std;

map<string, string> parseEnvFile(const string& filename) {
    map<string, string> envMap;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string key, value;
        if (getline(getline(iss >> ws, key, '='), value)) {
            envMap[key] = value;
        }
    }

    return envMap;
}

EnvManager::EnvManager()
{
    envVars = parseEnvFile("../.env");
}

string EnvManager::getParam(string paramName)
{
    auto it = envVars.find(paramName);
    if (it != envVars.end()) {
        return it->second;
    } else {
        return "";
    }
}
