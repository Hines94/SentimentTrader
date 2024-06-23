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
fi