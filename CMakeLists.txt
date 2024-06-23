
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name
project(SentimentTrader)

include_directories(src)
file(GLOB_RECURSE LIB_SOURCES "./src/*.cpp")
# Add an executable target
add_executable(SentimentTrader ${LIB_SOURCES})

# Setup packages
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

target_link_libraries(SentimentTrader ${CURL_LIBRARIES})