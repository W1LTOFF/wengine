cmake_minimum_required(VERSION 3.30)

# Variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

file(GLOB WENGINE_LIB_CORE_SRC
    src/wengine/core/*.cpp
)
file(GLOB WENGINE_LIB_GUI_SRC
    src/wengine/gui/*.cpp
)

set(WENGINE_LIB_ALL_SRC ${WENGINE_LIB_CORE_SRC} ${WENGINE_LIB_GUI_SRC})

add_subdirectory(include/imgui)
add_subdirectory(include/glad)

# Project
project(wengine)

# Create library
add_library(${PROJECT_NAME} STATIC ${WENGINE_LIB_ALL_SRC})

link_directories(${PROJECT_SOURCE_DIR}/lib)

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/imgui)

add_subdirectory(examples)

# file(COPY lib/glfw3.dll DESTINATION .)
