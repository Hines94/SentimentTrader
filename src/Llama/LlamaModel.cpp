#include <string>
#include <array>
#include <memory>

using namespace std;

string runLLaMA(const string& input) {
    string command = "../llama.cpp/build/bin/llama-cli -m ../llama.cpp/models/llama-2-7b.Q5_K_M.gguf -p ";
    string fullCommand = command + " \"" + input + "\" -e";
    
    array<char, 128> buffer;
    string result;

    // Open a pipe to run the command
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(fullCommand.c_str(), "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}