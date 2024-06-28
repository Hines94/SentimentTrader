#include "LlamaModel.h"
#include <string>
#include <array>
#include <memory>
#include <iostream>
#include <string.h>

using namespace std;

LlamaModel::LlamaModel()
{
    //https://github.com/ggerganov/llama.cpp/tree/master/examples/finetune
}

void LlamaModel::InitLlama(const string& modelPath) {
    // Build the command string
    string command = "../llama.cpp/build/bin/llama-cli -m \"" + modelPath + "\" -if -n20 -e";
    
    // Log the command to be executed
    cout << "Executing command: " << command << endl;

    // Open the pipe for reading and writing
    pipe = popen(command.c_str(), "r");
    if (!pipe) {
        // Capture the errno for additional debugging information
        int err = errno;
        throw runtime_error("popen() failed while initializing Llama model! Error: " + string(strerror(err)));
    }
}

LlamaModel::~LlamaModel() {
    if (pipe) {
        // Send an exit command or handle shutdown if necessary
        fprintf(pipe, "exit\n");
        fflush(pipe);
        pclose(pipe);
    }
}

string LlamaModel::runLLaMA(const string& input) {
    if(pipe == nullptr) {
        throw runtime_error("Llama not setup correctly. Use LlamaModel::InitLlama");
    }

    cout << "Processing Llama input: " << input << endl;

    string result;
    array<char, 128> buffer;

    // Write input to the pipe
    fprintf(pipe, "%s\n", input.c_str());
    fflush(pipe);

    // Read the output from the pipe
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
        // Check if we have received a complete response
        if (result.find("Some expected output end or prompt") != string::npos) {
            break;
        }
    }

    return result;
}