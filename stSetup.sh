#!/bin/bash

cd() {
    builtin cd "$@" || { echo "Failed to change directory" >&2; exit 1; }
}
confirm() {
    while true; do
        # Prompt the user for confirmation
        read -p "" yn

        # Check the input and act accordingly
        case $yn in
            [Yy]* )  return 0;;
            [Nn]* )  return 1;;
            * ) echo "Please answer y or n.";;
        esac
    done
}

echo "Update cmake and g++?"

if confirm; then
    sudo apt update
    sudo apt install cmake g++
fi

echo "Install LLama Cpp?"
if confirm; then
    git clone https://github.com/ggerganov/llama.cpp
    cd llama.cpp
    cmake -B build
    cmake --build build --config Release
    cd ../
fi

echo "Install Llama-2-7B-GGUF quantized Model?"
if confirm; then
    model_url="https://huggingface.co/TheBloke/Llama-2-7B-GGUF/resolve/main/llama-2-7b.Q5_K_M.gguf?download=true"
    mkdir llama.cpp/models
    destination_folder="llama.cpp/models"
    wget -P "$destination_folder" "$model_url"
    mv llama.cpp/models/llama-2-7b.Q5_K_M.gguf?download=true llama.cpp/models/llama-2-7b.Q5_K_M.gguf
fi

echo "Install required packages?"
if confirm; then 
    sudo apt-get install libcurl4-openssl-dev
fi