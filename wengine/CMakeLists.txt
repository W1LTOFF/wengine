cmake_minimum_required(VERSION 3.30)

# Variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

file(GLOB WENGINE_LIB_CORE_SRC
    "src/core/*.cpp"
)

set(WENGINE_LIB_ALL_SRC ${WENGINE_LIB_CORE_SRC})

# Project
project(wengine)

# Create library
add_library(${PROJECT_NAME} STATIC ${WENGINE_LIB_ALL_SRC})

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/imgui)

